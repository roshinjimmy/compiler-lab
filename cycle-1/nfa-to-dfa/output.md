Enter number of NFA states: 3
Enter number of input symbols: 2
Enter input symbols:
Symbol 1: a
Symbol 2: b

Enter NFA transitions:
From q0 on 'a', number of transitions: 1
  Enter destination state: 1
From q0 on 'b', number of transitions: 0
From q1 on 'a', number of transitions: 0
From q1 on 'b', number of transitions: 1
  Enter destination state: 2
From q2 on 'a', number of transitions: 0
From q2 on 'b', number of transitions: 1
  Enter destination state: 2

DFA Transition Table:
DFA State 0 [q0 ]:
  On 'a' -> DFA State 1
  On 'b' -> DFA State 2
DFA State 1 [q1 ]:
  On 'a' -> DFA State 2
  On 'b' -> DFA State 3
DFA State 2 []:
  On 'a' -> DFA State 2
  On 'b' -> DFA State 2
DFA State 3 [q2 ]:
  On 'a' -> DFA State 2
  On 'b' -> DFA State 3