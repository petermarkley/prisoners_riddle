# Riddle of 100 Prisoners and a Lightbulb

There is a more classical version of this logic problem, but I am using the modified version posed by [`@evan_db_dub` on Tik Tok](https://www.tiktok.com/@evan_db_dub).

Video posing the riddle: https://www.tiktok.com/@evan_db_dub/video/7186126660859645226

Transcribed here:
> One hundred prisoners are sentenced to life in prison, in solitary confinement. Upon arrival at the prison, the warden proposes a deal to keep them entertained. The warden has a large bowl containing the cell numbers of all the prisoners. Each day, he randomly chooses one cell from the bowl. The corresponding prisoner is taken to the interrogation room, and the cell number is returned to the bowl. While in the interrogation room, the prisoner will not be allowed to touch anything except the light switch, which the prisoner may choose to turn on or off. The prisoner may make the assertion that all one hundred prisoners have been in the room. If the prisoner's assertion is correct, all prisoners will be released. If the prisoner is incorrect, the game is over and their chance to be freed is gone. The prisoners are given one meeting to discuss a strategy before the communication is completely severed. What strategy should they adopt in order to ensure with one hundred percent certainty that one of them will guess it correctly and all will be freed? The prisoners do not know if the light switch is initially on or off.

As Evan noted in a later video, the last detail given (that the light begins in an unknown state) is a departure from the classical version of the riddle.

Before I heard Evan's solution, I thought of one myself (although regrettably didn't write or post it anywhere). As it turned out, Evan's solution differed from mine, and both solutions work. In fact, my solution works twice as fast.

This software simulates the prison scenario and both solutions, to prove that they both work and that mine is faster.

## Evan's Solution

- https://www.tiktok.com/@evan_db_dub/video/7187605933026086190
- https://www.tiktok.com/@evan_db_dub/video/7187627231923948842

One prisoner is chosen as the "counter."

### Instructions for the Counter

- Every time he finds the light on, he turns it off. He keeps count of how many times.
- When his count reaches 198, he knows all 100 prisoners have been in the room.

### Instructions for General Prisoners

- The first two times the prisoner enters and finds the light off, he turns it on, then never touches it again.

### Comments

This solution mimics the classical solution, but accommodates the unknown starting condition by the use of simple redundancy. If the light is on at the beginning, each of the 99 "general" prisoners will turn it off exactly twice except for one of them: he will turn it off exactly once, which is good enough.

Compared to my solution, this has simpler instructions but worse performance by a factor of two.

### Simulation

Evan's solution is simulated in the file `prisoners-solution-2.c`:

```
make
./prisoners-2
```

With this strategy, the prisoners are freed after an average of 20,000 days (or about 55 years).

## My Solution

Just like the "counter" in Evan's solution, one prisoner is designated as an "information-gatherer." He will have his own instructions, and all the others will follow another set of instructions.

### Instructions for Designated Counter

- If the light is off and it's his first visit to the room, he turns the light on, then never again. (If the light is already on for his first visit, he will never turn it on at all.)
- Every time he comes in and finds the light on, he will turn it off. The first time he does this, he skips counting. Ever afterward, he keeps count.
- When his count reaches 99, he knows all 100 prisoners have been in the room.

### Instructions for General Prisoners

- The prisoner waits and does nothing until he has entered and found the light on at least once.
- After that point, the next time he finds the light off, he turns it on, then never touches it again.

### Comments

In this way, the designated counter normalizes the starting condition so that it quickly converges with the classical version of the puzzle. He knows for certain that the first time he turns the light off, none of the other prisoners turned it on: either because it started on, or because he's the one who turned it on.

When he turns the light off, it indirectly signals to all the other prisoners that they are free to flip the switch once each without fear of contanimating the context.

While I was still pondering the riddle, I heard about the modification Evan made on the classical version. So I began by solving the classical version, then modified my solution to accommodate Evan's new version. That's why mine converges in the way that it does.

### Simulation

My solution is simulated in the file `prisoners-solution-1.c`:

```
make
./prisoners-1
```

With this strategy, the prisoners are freed after an average of 10,000 days (or about 27 years).
