Enter number of states: 3
Enter number of input symbols: 2
Enter the input symbols (excluding ε):
Symbol 1: a
Symbol 2: b

Enter transitions for each state and symbol:
From q0 on 'a': how many transitions? 0
From q0 on 'b': how many transitions? 0
From q1 on 'a': how many transitions? 1
  Enter destination state 1: 2
From q1 on 'b': how many transitions? 0
From q2 on 'a': how many transitions? 0
From q2 on 'b': how many transitions? 1
  Enter destination state 1: 1

Enter epsilon transitions:
From q0: how many ε-transitions? 1
  Enter destination state 1: 1
From q1: how many ε-transitions? 1
  Enter destination state 1: 2
From q2: how many ε-transitions? 0

NFA without ε-transitions:
From q0 on 'a': { q2 }
From q0 on 'b': { q1 q2 }
From q1 on 'a': { q2 }
From q1 on 'b': { q1 q2 }
From q2 on 'a': { }
From q2 on 'b': { q1 q2 }