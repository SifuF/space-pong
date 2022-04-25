# Space Pong
Pong game featuring tough CPU opponents.

![Pong image](img/pong.gif)

### CPU opponents

Easy mode just moves towards the puck's vertical position and is easy to beat... hard mode integrates the puck velocity and moves towards its intersection with the paddle axis.

Serve strategy is to move a random distance up or down from the intersection (to give a random return trajectory).

After a serve, it can either stay still, move back to the centre, or mirror the other player.

[Click here for video](img/pong.mp4)

![Pong image](img/sp1.png)

```
Left paddle:
  Up/Down: Q/A
  CPU On/Off : W/S

Right paddle:
  Up/Down: Up arrow/Down arrow
  CPU On/Off : O/L

Difficulty:
  Easy: V
  Hard-Stay : B
  Hard-Reset: N
  Hard-Follow: M

Game speed Up/Down : T/G
Reset game: R
Debug On/Off : E/D
```
