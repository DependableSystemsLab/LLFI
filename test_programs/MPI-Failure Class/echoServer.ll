; ModuleID = 'echoServer.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-f128:128:128-n8:16:32:64"
target triple = "x86_64-unknown-linux-gnu"

%struct.in_addr = type { i32 }
%struct.sockaddr = type { i16, [14 x i8] }
%struct.sockaddr_in = type { i16, i16, %struct.in_addr, [8 x i8] }

@.str = private unnamed_addr constant [42 x i8] c"Server running...waiting for connections.\00", align 8
@.str1 = private unnamed_addr constant [20 x i8] c"Received request...\00", align 1
@.str2 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str3 = private unnamed_addr constant [47 x i8] c"String received from and resent to the client:\00", align 8
@.str4 = private unnamed_addr constant [11 x i8] c"Read error\00", align 1

define i32 @main(i32 %argc, i8** %argv) nounwind {
entry:
  %argc_addr = alloca i32, align 4
  %argv_addr = alloca i8**, align 8
  %retval = alloca i32
  %listenfd = alloca i32
  %connfd = alloca i32
  %n = alloca i32
  %clilen = alloca i32
  %buf = alloca [4096 x i8]
  %cliaddr = alloca %struct.sockaddr_in
  %servaddr = alloca %struct.sockaddr_in
  %"alloca point" = bitcast i32 0 to i32
  store i32 %argc, i32* %argc_addr
  store i8** %argv, i8*** %argv_addr
  %0 = call i32 @socket(i32 2, i32 1, i32 0) nounwind
  store i32 %0, i32* %listenfd, align 4
  %1 = getelementptr inbounds %struct.sockaddr_in* %servaddr, i32 0, i32 0
  store i16 2, i16* %1, align 4
  %2 = call i32 @htonl(i32 0) nounwind readnone
  %3 = getelementptr inbounds %struct.sockaddr_in* %servaddr, i32 0, i32 2
  %4 = getelementptr inbounds %struct.in_addr* %3, i32 0, i32 0
  store i32 %2, i32* %4, align 4
  %5 = call zeroext i16 @htons(i16 zeroext 3000) nounwind readnone
  %6 = getelementptr inbounds %struct.sockaddr_in* %servaddr, i32 0, i32 1
  store i16 %5, i16* %6, align 2
  %servaddr1 = bitcast %struct.sockaddr_in* %servaddr to %struct.sockaddr*
  %7 = load i32* %listenfd, align 4
  %8 = call i32 @bind(i32 %7, %struct.sockaddr* %servaddr1, i32 16) nounwind
  %9 = load i32* %listenfd, align 4
  %10 = call i32 @listen(i32 %9, i32 8) nounwind
  %11 = call i32 @puts(i8* getelementptr inbounds ([42 x i8]* @.str, i64 0, i64 0)) nounwind
  br label %bb

bb:                                               ; preds = %bb12, %entry
  store i32 16, i32* %clilen, align 4
  %cliaddr3 = bitcast %struct.sockaddr_in* %cliaddr to %struct.sockaddr*
  %12 = load i32* %listenfd, align 4
  %13 = call i32 @accept(i32 %12, %struct.sockaddr* noalias %cliaddr3, i32* noalias %clilen) nounwind
  store i32 %13, i32* %connfd, align 4
  %14 = call i32 @puts(i8* getelementptr inbounds ([20 x i8]* @.str1, i64 0, i64 0)) nounwind
  br label %bb8

bb5:                                              ; preds = %bb8
  %15 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([3 x i8]* @.str2, i64 0, i64 0), i8* getelementptr inbounds ([47 x i8]* @.str3, i64 0, i64 0)) nounwind
  %buf6 = bitcast [4096 x i8]* %buf to i8*
  %16 = call i32 @puts(i8* %buf6) nounwind
  %17 = load i32* %n, align 4
  %18 = sext i32 %17 to i64
  %19 = load i32* %connfd, align 4
  %buf7 = bitcast [4096 x i8]* %buf to i8*
  %20 = call i64 @send(i32 %19, i8* %buf7, i64 %18, i32 0) nounwind
  br label %bb8

bb8:                                              ; preds = %bb5, %bb
  %21 = load i32* %connfd, align 4
  %buf9 = bitcast [4096 x i8]* %buf to i8*
  %22 = call i64 @recv(i32 %21, i8* %buf9, i64 4096, i32 0) nounwind
  %23 = trunc i64 %22 to i32
  store i32 %23, i32* %n, align 4
  %24 = load i32* %n, align 4
  %25 = icmp sgt i32 %24, 0
  br i1 %25, label %bb5, label %bb10

bb10:                                             ; preds = %bb8
  %26 = load i32* %n, align 4
  %27 = icmp slt i32 %26, 0
  br i1 %27, label %bb11, label %bb12

bb11:                                             ; preds = %bb10
  call void @perror(i8* getelementptr inbounds ([11 x i8]* @.str4, i64 0, i64 0)) nounwind
  call void @exit(i32 1) noreturn nounwind
  unreachable

bb12:                                             ; preds = %bb10
  %28 = load i32* %connfd, align 4
  %29 = call i32 @close(i32 %28) nounwind
  br label %bb

return:                                           ; No predecessors!
  %retval13 = load i32* %retval
  ret i32 %retval13
}

declare i32 @socket(i32, i32, i32) nounwind

declare i32 @htonl(i32) nounwind readnone

declare zeroext i16 @htons(i16 zeroext) nounwind readnone

declare i32 @bind(i32, %struct.sockaddr*, i32) nounwind

declare i32 @listen(i32, i32) nounwind

declare i32 @puts(i8*)

declare i32 @accept(i32, %struct.sockaddr* noalias, i32* noalias)

declare i32 @printf(i8* noalias, ...) nounwind

declare i64 @send(i32, i8*, i64, i32)

declare i64 @recv(i32, i8*, i64, i32)

declare void @perror(i8*)

declare void @exit(i32) noreturn nounwind

declare i32 @close(i32)
