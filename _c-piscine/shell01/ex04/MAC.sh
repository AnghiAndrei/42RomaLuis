ifconfig -a | grep ether | awk '{print $2}' | tr '\n' '\n'
