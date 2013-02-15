#!/usr/bin/expect -f

set timeout 60 
spawn lli -load=/usr/lib/libcrypto.so -load=/usr/lib/libdl.so -load=/usr/lib/libutil.so -load=/usr/lib/libz.so -load=/usr/lib/libnsl.so -load=/usr/lib/libcrypt.so -load=/usr/lib/libresolv.so ssh.final_inject.bs.bc llfi@sdf.org

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
