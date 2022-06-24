## HW2

#### a. Scoreboard

| instruction    | Issue | Comp | Result |
| -------------- | ----- | ---- | ------ |
| LD F6,34(R2)   | 1     | 3    | 4      |
| LD F2,45(R3)   | 5     | 7    | 8      |
| MUL.D F0.F2.F4 | 6     | 19   | 20     |
| SUB.D F8.F2.F6 | 7     | 11   | 12     |
| DIV F10.F0.F6  | 8     | 61   | 62     |
| ADD.D F6,F8,F2 | 13    | 16   | 22     |

#### b.Tomasulo

| instruction    | Issue | Comp | Result |
| -------------- | ----- | ---- | ------ |
| LD F6,34(R2)   | 1     | 3    | 4      |
| LD F2,45(R3)   | 2     | 4    | 5      |
| MUL.D F0.F2.F4 | 3     | 15   | 16     |
| SUB.D F8.F2.F6 | 4     | 7    | 8      |
| DIV F10.F0.F6  | 5     | 56   | 57     |
| ADD.D F6,F8,F2 | 6     | 10   | 11     |

