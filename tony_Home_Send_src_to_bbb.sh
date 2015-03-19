#!/bin/bash

# A = ${OPTARG};

# if [ -z "$EXEC_FILE_NAME" ] then
	scp -r ~/Desktop/repositories/quadcopter-beagle/workspace/BBB_testing/src/ root@192.168.2.19:/source_code_test/
	# ssh root@192.168.2.19 'gcc -o /source_code_test/src/$A /source_code_test/src/BBB_testing.c /source_code_test/src/onboard_led_control.c'
	# ssh root@192.168.2.19 'echo "$A has been created in /source_code_test/src/"'
# else 
# echo "Proper syntax: bash tony_Home_Send_src_to_bbb <Name of executable>";
# fi