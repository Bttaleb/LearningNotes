Inactivity Sign-out
"What are we building?"
- If a signed in user is inactive for 15 minutes, show a 60 second warning. If they don't respond, sign them out and send them back to login
## Problem Decomposition

| Edge Cases                               | What Should Happen?                        |
| ---------------------------------------- | ------------------------------------------ |
| User on welcome/login                    | Time DOES NOT run                          |
| User taps on screen during warning       | "Stay signed in" resets everything         |
| App backgrounded for 20 minutes          | Logout on return                           |
| Supabase not configured                  | App still clears local state and navigates |
| User hits "start new session" on results | Same logout path as inactivity             |
Separation of Concerns

| Piece                    | Location                                     | Why Here?                                                         |
| ------------------------ | -------------------------------------------- | ----------------------------------------------------------------- |
| Timeout values           | app.config.ts + src/config/sessionTimeout.ts | Config at the edge -> app code reads typed constant               |
| Logout Orchestration     | src/services/session/endSession.ts           | sits next to startPracticeSession, symmetric "enter/exit session" |
| Idle detection + timeout | src/providers/inactivityProviders.tsx        | every authenticated screen                                        |
| Warning UI               | src/components/SessionTimeoutModal.tsx       | Pure presentation                                                 |

