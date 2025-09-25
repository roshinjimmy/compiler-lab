Enter expression ending with #: id+id*id#

Step  Stack                Input                Action         
---------------------------------------------------------------
1     #                    id+id*id#            Shift          
2     #id                  +id*id#              Reduce         
3     #E                   +id*id#              Shift          
4     #E+                  id*id#               Shift          
5     #E+id                *id#                 Reduce         
6     #E+E                 *id#                 Shift          
7     #E+E*                id#                  Shift          
8     #E+E*id              #                    Reduce         
9     #E+E*E               #                    Reduce         
10    #E+E                 #                    Reduce         
11    #E                   #                    Accept         

Expression Accepted!