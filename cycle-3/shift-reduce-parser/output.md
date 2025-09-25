Enter input:
i+i-i
Stack           Input           Action
$               i+i-i$          SHIFT
stack = 
$i              +i-i$           REDUCE
$S              +i-i$           SHIFT
stack = S
$S+             i-i$            SHIFT
stack = S+
$S+i            -i$             REDUCE
$S+S            -i$             REDUCE
$S+             -i$             SHIFT
stack = S+S
$S-S            i$              SHIFT
stack = S-S
$S-i            $               REDUCE
$S-S            $               REDUCE
Accepted.