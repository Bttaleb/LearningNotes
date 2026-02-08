---
date: "January 20, 2026"
project: "saraBeauty1.0"
---

# Swift + Supabase Learning Notes

# Part 1: Architecture & Structure

## 1.1 Service Architecture

### Problem
Having separate services for related operations (`CreatePostService` + `FeedService`) creates fragmentation.

### Solution
Combine into a single service per domain:

```swift
struct PostService {
    func fetchPosts() async throws -> [Post] { ... }
    func createPost(...) async throws { ... }
    func deletePost(id: String) async throws { ... }
}
```

### Rule of Thumb
- One service per domain (Posts, Comments, Users)
- Each service handles all CRUD operations for that domain

---

## 1.2 Navigation Patterns

### Post + Comments: Detail View Pattern

| Pattern | Description | Use Case |
|---------|-------------|----------|
| **Detail View** | Tap post → Navigate to full post + comments | Reddit, Twitter |
| Bottom Sheet | Tap icon → Slide up comments | Instagram |
| Expandable Inline | Comments expand under post | Thread-style |

### Implementation Flow
```
PostView (feed)
    → PostCell (tappable via NavigationLink)
        → PostDetailView (post + comments + input bar)
```

### Key Code
```swift
NavigationLink(destination: PostDetailView(post: post)) {
    // cell content
}
.buttonStyle(.plain)
```

---

# Part 2: Supabase & Database

## 2.1 Common Database Errors

### Error: "null value in column X violates not-null constraint"

**Cause:** Swift code isn't providing a required field.

| Field | Swift Fix | Supabase Fix |
|-------|-----------|--------------|
| `id` | `id: UUID().uuidString` | Default: `gen_random_uuid()` |
| `createdAt` | `createdAt: Date()` | Default: `now()` |
| `parent_id` | N/A (should allow null) | Uncheck "Is Nullable" |

**Example:**
```swift
struct CommentInsert: Encodable {
    let id: String
    let post_id: String
    let user_id: String
    let content: String
    let parent_id: String?
    let createdAt: Date
}

let data = CommentInsert(
    id: UUID().uuidString,
    post_id: postId,
    user_id: userId,
    content: content,
    parent_id: parentId,  // Use actual parameter, NOT UUID()!
    createdAt: Date()
)
```

---

### Error: "violates foreign key constraint"

**Cause:** Inserting a value that doesn't exist in the referenced table.

```swift
// WRONG - generates random ID that doesn't exist
parent_id: UUID().uuidString

// CORRECT - uses actual parent ID (or nil)
parent_id: parentId
```

---

### Error: "permission denied for table X"

**Cause:** Row Level Security (RLS) is blocking access.

**Fix:** Add a SELECT policy:
```sql
CREATE POLICY "Allow authenticated users to read users"
ON users FOR SELECT TO authenticated USING (true);
```

---

### Error: "Expected to decode Double but found a string"

**Cause:** Supabase returns dates as ISO 8601 strings.

**Fix:** Configure the decoder (apply to ALL decode calls):
```swift
let decoder = JSONDecoder()
decoder.dateDecodingStrategy = .iso8601
let comments = try decoder.decode([Comment].self, from: response.data)
```

---

## 2.2 Database Triggers

### Problem
When a user updates their profile picture, it should update everywhere (posts, comments).

### Solution: PostgreSQL Trigger
```sql
CREATE OR REPLACE FUNCTION update_author_profile_images()
RETURNS TRIGGER AS $$
BEGIN
    UPDATE posts
    SET "authorProfileImageURL" = NEW.profile_image_url
    WHERE "authorID" = NEW.id::text;

    UPDATE comments
    SET author_profile_image_url = NEW.profile_image_url
    WHERE user_id = NEW.id::text;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER on_profile_image_update
AFTER UPDATE OF profile_image_url ON users
FOR EACH ROW
WHEN (OLD.profile_image_url IS DISTINCT FROM NEW.profile_image_url)
EXECUTE FUNCTION update_author_profile_images();
```

---

## 2.3 Column Name Mapping

| Swift Property | Database Column | Notes |
|----------------|-----------------|-------|
| `createdAt` | `created_at` or `createdAt` | Check your table |
| `profileImageURL` | `profile_image_url` | Snake case in DB |
| `postId` | `post_id` | Usually snake case |

**Always check your model's `CodingKeys` enum!**

---

# Part 3: SwiftUI State Management

> This section covers when and how to use different state types.

## 3.1 Choosing the Right State Type

| Need | Use | Example |
|------|-----|---------|
| Simple local value | `@State` | `@State private var isCollapsed = true` |
| Pass state to child | `@Binding` | `@Binding var text: String` |
| Shared across views | `@Observable` class | `UserManager`, `AuthManager` |
| From environment | `@Environment` | `@Environment(UserManager.self)` |

### When to Simplify

**Before (unnecessary complexity):**
```swift
@Observable class StoreManager {
    var isShowingSubscriptions = false
}

struct MyView: View {
    @State private var vm = StoreManager()
}
```

**After (simple @State):**
```swift
struct MyView: View {
    @State private var showSubscription = false
}
```

**Rule:** Only use `@Observable` classes when you need shared state, complex logic, or dependency injection. For simple booleans → use `@State`.

---

## 3.2 @State Initialization

### Three Ways to Set Initial Value

**1. Inline default (simplest)**
```swift
@State private var isCollapsed: Bool = true
```

**2. Custom init (dynamic defaults)**
```swift
@State private var isCollapsed: Bool = true  // Gets overridden!

init(depth: Int) {
    self._isCollapsed = State(initialValue: depth > 0)
}
```

**3. Required in init**
```swift
@State private var isCollapsed: Bool  // No default

init(depth: Int) {
    self._isCollapsed = State(initialValue: depth > 0)
}
```

### Common Pitfall: Init Overrides Default

```swift
@State private var isCollapsed: Bool = true  // You think this is the default

init(depth: Int) {
    self._isCollapsed = State(initialValue: depth > 0)  // Actually THIS runs
}
```

The inline `= true` is **ignored** because the init overrides it.

---

### The Underscore & Dollar Sign

```swift
@State private var isCollapsed: Bool = true
```

| Access | Type | Use for |
|--------|------|---------|
| `isCollapsed` | `Bool` | Reading/writing the value |
| `_isCollapsed` | `State<Bool>` | Setting initial value in init |
| `$isCollapsed` | `Binding<Bool>` | Passing to child views |

> **Connection:** When you use `@Binding` in a child view, the parent passes `$stateVariable` to provide that binding. See **Section 3.1**.

---

### Practical Example: Collapse Behavior

| Desired behavior | Code |
|------------------|------|
| All collapsed | `@State private var isCollapsed = true` |
| All expanded | `@State private var isCollapsed = false` |
| Parent expanded, children collapsed | `State(initialValue: depth > 0)` |
| Parent collapsed, children expanded | `State(initialValue: depth == 0)` |

---

# Part 4: SwiftUI UI Patterns

## 4.1 ViewModifiers (Reusable Components)

### Problem
Repeating the same sheet/modifier code across multiple views.

### Solution
```swift
struct SubscriptionSheetModifier: ViewModifier {
    @Binding var isPresented: Bool
    var onPurchaseComplete: ((String) -> Void)?

    func body(content: Content) -> some View {
        content
            .sheet(isPresented: $isPresented) {
                SubscriptionStoreView(groupID: "YOUR_GROUP_ID")
                    .onInAppPurchaseCompletion { product, result in
                        onPurchaseComplete?(product.id)
                        isPresented = false
                    }
            }
    }
}

extension View {
    func subscriptionSheet(
        isPresented: Binding<Bool>,
        onPurchaseComplete: ((String) -> Void)? = nil
    ) -> some View {
        modifier(SubscriptionSheetModifier(
            isPresented: isPresented,
            onPurchaseComplete: onPurchaseComplete
        ))
    }
}
```

### Usage
```swift
Button("Subscribe") { showSubscription = true }
    .subscriptionSheet(isPresented: $showSubscription)
```

> **Connection:** Note the `@Binding var isPresented` - this connects to **Section 3.1** on state types. The parent owns the `@State`, the modifier receives a `@Binding`.

---

## 4.2 Thread Lines (Visual Nesting)

### Problem
Nested comments are hard to follow without visual indicators.

### Solution
```swift
if !comment.replies.isEmpty && !isCollapsed {
    HStack(alignment: .top, spacing: 12) {
        Rectangle()
            .fill(Color.gray.opacity(0.3))
            .frame(width: 2)

        VStack(alignment: .leading, spacing: 8) {
            ForEach(comment.replies) { reply in
                CommentCell(comment: reply, depth: depth + 1, onReply: onReply)
            }
        }
    }
    .padding(.leading, 28)
}
```

### Why It Works
- `Rectangle()` with no fixed height stretches to fill the parent
- `alignment: .top` ensures line starts at the top

### Customization
```swift
// Colors per depth
let lineColors: [Color] = [.blue, .green, .orange, .purple]
Rectangle().fill(lineColors[depth % lineColors.count].opacity(0.4))

// Tappable (collapse on tap)
Rectangle().onTapGesture { isCollapsed.toggle() }
```

> **Connection:** The `isCollapsed` state here ties into **Section 3.2** on @State initialization. The `depth` parameter determines initial collapse state.

---

## 4.3 Collapsible Content with Rotating Chevron

### Structure
```swift
// Indicator (far right)
if !comment.replies.isEmpty {
    HStack(spacing: 4) {
        if isCollapsed {
            Text("\(count) \(count == 1 ? "reply" : "replies")")
                .font(.caption)
                .foregroundStyle(.secondary)
        }

        Image(systemName: "chevron.right")
            .rotationEffect(.degrees(isCollapsed ? 0 : 90))
            .animation(.default, value: isCollapsed)
    }
    .onTapGesture { isCollapsed.toggle() }
}

// Content (shows when expanded)
if !isCollapsed && !comment.replies.isEmpty {
    // nested content here
}
```

### Behavior
- **Collapsed:** `3 replies ›`
- **Expanded:** `˅` (chevron rotated 90°)

---

# Part 5: SwiftUI Previews

## 5.1 Why Previews Fail

Previews need **all dependencies** your view requires.

| Dependency | How to Provide |
|------------|----------------|
| `let comment: Comment` | Create full object |
| `let onReply: (Comment) -> Void` | `{ _ in }` or `{ comment in print(comment) }` |
| `@Binding var text: String` | `.constant("value")` |
| `@Environment(UserManager.self)` | `.environment(UserManager())` |
| Uses `NavigationLink` | Wrap in `NavigationStack { }` |

> **Connection:** The `@Binding` and `@Environment` here connect back to **Section 3.1** on state types.

---

## 5.2 Example: CommentCell Preview

```swift
#Preview("Single Comment") {
    CommentCell(
        comment: Comment(
            id: "1",
            postId: "post1",
            userId: "user1",
            parentId: nil,
            content: "Sample comment!",
            createdAt: Date(),
            authorUsername: "testuser",
            authorProfileImageUrl: nil
        ),
        depth: 0
    ) { _ in }
    .padding()
}
```

---

## 5.3 Pro Tip: Mock Extensions

```swift
extension Comment {
    static var mock = Comment(
        id: "1", postId: "post1", userId: "user1",
        parentId: nil, content: "Sample comment",
        createdAt: Date(), authorUsername: "testuser",
        authorProfileImageUrl: nil
    )
}
```

Then:
```swift
#Preview { CommentCell(comment: .mock, depth: 0) { _ in } }
```

---

## 5.4 Common Preview Mistakes

| Mistake | Fix |
|---------|-----|
| `Text("Hello")` instead of model | Create actual `Comment(...)` object |
| Missing closure `<#T##...#>` | Add `{ _ in }` |
| Forgot `NavigationStack` | Wrap view if it uses navigation |
| Missing `.environment()` | Add required environment objects |

---

# Part 6: Debugging

## Swift Debugging
```swift
let _ = print("isCollapsed: \(isCollapsed)")  // Print in view body
print("DEBUG: \(error)")                       // Print errors
```

## Supabase Debugging
1. **Dashboard → Logs → Postgres** for SQL errors
2. **SQL Editor** to test queries directly
3. **Authentication → Policies** to verify RLS

## State Not Working?
1. Check for init override (`self._isCollapsed = ...`)
2. Print initial value
3. Verify condition logic (`depth > 0` vs `depth == 0`)

---

# Quick Reference

## Condition Logic
```swift
depth > 0   // true when depth is 1, 2, 3...
depth == 0  // true only when depth is 0
depth >= 1  // same as depth > 0
!isCollapsed && !replies.isEmpty  // expanded AND has replies
```

## State Access
```swift
isCollapsed      // Bool value
_isCollapsed     // State wrapper (for init)
$isCollapsed     // Binding (pass to children)
```
