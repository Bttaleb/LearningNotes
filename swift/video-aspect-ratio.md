---
tags:
  - media
  - async
  - ui-patterns
source: "saraBeauty1.0 project (Jan 2026)"
description: "Dynamically detect and apply video dimensions in SwiftUI"
---

# Video Aspect Ratio Handling


## The Problem

Videos come in different aspect ratios:
- **16:9** — Standard landscape (YouTube)
- **9:16** — Portrait (TikTok, Reels)
- **1:1** — Square (Instagram)
- **4:3** — Classic TV

Hardcoding `.aspectRatio(16/9)` breaks layout for non-standard videos.

---

## Solution: AVURLAsset

Use `AVURLAsset` to fetch video metadata (including dimensions) without fully downloading the video.

### The Helper

```swift
import AVFoundation

enum VideoAspectRatioHelper {

    static func getAspectRatio(from url: URL) async -> CGFloat {
        let asset = AVURLAsset(url: url)

        do {
            // Load video tracks
            let tracks = try await asset.loadTracks(withMediaType: .video)
            guard let track = tracks.first else { return 16/9 }

            // Get natural size and transform
            let size = try await track.load(.naturalSize)
            let transform = try await track.load(.preferredTransform)

            // Apply transform (handles rotated videos)
            let transformedSize = size.applying(transform)
            let width = abs(transformedSize.width)
            let height = abs(transformedSize.height)

            guard height > 0 else { return 16/9 }
            return width / height

        } catch {
            return 16/9  // Fallback
        }
    }
}
```

### Why `preferredTransform`?

Videos can be rotated in metadata (especially from phones). The raw `naturalSize` might report 1920x1080, but the video displays as 1080x1920 (portrait). Applying the transform gives the actual display dimensions.

---

## Usage in SwiftUI

### In a View

```swift
struct VideoPlayerView: View {
    let videoURL: URL

    @State private var aspectRatio: CGFloat = 16/9  // Default
    @State private var player: AVPlayer?

    var body: some View {
        VideoPlayer(player: player)
            .aspectRatio(aspectRatio, contentMode: .fit)
            .task {
                // Fetch actual ratio when view appears
                aspectRatio = await VideoAspectRatioHelper.getAspectRatio(from: videoURL)
                player = AVPlayer(url: videoURL)
            }
    }
}
```

### Key Points

| Concept | Explanation |
|---------|-------------|
| `@State private var aspectRatio` | Starts with default, updates when fetched |
| `.task { }` | Runs async code when view appears |
| `.aspectRatio(_, contentMode: .fit)` | Scales to fit container while preserving ratio |
| `.aspectRatio(_, contentMode: .fill)` | Fills container, may crop edges |

---

## For Thumbnails (No Video Load)

If you don't want to load video metadata for thumbnails:

```swift
AsyncImage(url: thumbnailURL) { image in
    image
        .resizable()
        .aspectRatio(contentMode: .fit)  // Preserves natural ratio
}
.frame(maxWidth: .infinity)
.frame(minHeight: 180, maxHeight: 300)  // Flexible height range
.background(Color(.systemGray6))        // Fill empty space
```

This lets the image determine its own ratio within height bounds.

---

## Common Aspect Ratios

| Ratio | Decimal | Use Case |
|-------|---------|----------|
| 16:9 | 1.78 | YouTube, TV |
| 9:16 | 0.56 | TikTok, Stories |
| 4:3 | 1.33 | Classic TV, iPad |
| 1:1 | 1.0 | Instagram square |
| 21:9 | 2.33 | Cinematic |
