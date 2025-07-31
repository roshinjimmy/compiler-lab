Enter number of states in DFA: 4
Enter number of input symbols: 2
Enter input symbols:
Symbol 1: a
Symbol 2: b

Enter transition table (destination state for each input):
From q0 on 'a': 1
From q0 on 'b': 2
From q1 on 'a': 1
From q1 on 'b': 3
From q2 on 'a': 1
From q2 on 'b': 3
From q3 on 'a': 3
From q3 on 'b': 3
Enter number of final states: 1
Enter final state numbers: 3

Minimized DFA Transition Table:
State 0 [q0 ]:
  On 'a' -> State 1
  On 'b' -> State 1
State 1 [q1 q2 ]:
  On 'a' -> State 1
  On 'b' -> State 2
State 2 [q3 ]:
  On 'a' -> State 2
  On 'b' -> State 2