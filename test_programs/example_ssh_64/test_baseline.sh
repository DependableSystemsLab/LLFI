#!/usr/bin/expect -f
#timeout is a predefined variable in expect which by default is set to 10 sec
#spawn_id is another default variable in expect. 
#It is good practice to close spawn_id handle created by spawn command
set timeout 60 
spawn lli -load=/usr/lib/libcrypto.so -load=/usr/lib/libdl.so -load=/usr/lib/libutil.so -load=/usr/lib/libz.so -load=/usr/lib/libnsl.so -load=/usr/lib/libcrypt.so -load=/usr/lib/libresolv.so ssh.bc llfi@sdf.org

expect {
	"password:"	{send "llfitest\r"}
}

expect {
	"BACKSPACE"	{send "\b"}
}

while {1} {
expect {
	"continue"	{send "\r"}
	">"	{send "ls\r"
		break	}
}
}

expect {
	">"	{send "exit\r"}
}

while {1} {
	expect {
		eof	{break}
	}
}
