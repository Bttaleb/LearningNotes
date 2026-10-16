an agreement between two parties about what the bytes mean
- a contract both sides follow so the **receiver** can rebuild exactly what the sender meant
eg.
The kernel moves raw bytes through the *pipe* and nothing else. It has no idea what a "job" or a "result" is so the **coordinator** writes this

```
48 65 6C 6C 6F 57 6F 72 6C 64
```

The worker **CAN'T** tell that's one message ("HelloWorld"), two messages ("Hello World"), or half of a bigger message that hasn't fully arrived yet

- Bytes carry no structure
- Protocol supplies the structure

Every wire protocol answers three questions

| Question | What it means                                 |
| -------- | --------------------------------------------- |
| Framing  | Where does one message end and the next begin |
| Typing   | What *kind* of message is this                |
| Encoding | How is the payload laid out inside            |
One message on the wire looks like:

```
len (4 bytes) | type (1) | payload (len bytes)

```
