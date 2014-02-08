; ModuleID = '/ubc/ece/home/kp/grads/raiyat/newproject/LLFI-Cisco-master/test_programs/deadlock/deadlock.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-f128:128:128-n8:16:32:64"
target triple = "x86_64-unknown-linux-gnu"

%struct.__pthread_list_t = type { %struct.__pthread_list_t*, %struct.__pthread_list_t* }
%struct.__pthread_mutex_s = type { i32, i32, i32, i32, i32, i32, %struct.__pthread_list_t }
%union.pthread_attr_t = type { i64, [12 x i32] }
%union.pthread_mutex_t = type { %struct.__pthread_mutex_s }

@mutex1 = unnamed_addr global %union.pthread_mutex_t zeroinitializer, align 32
@.str = private unnamed_addr constant [8 x i8] c"Thread1\00", align 1
@.str1 = private unnamed_addr constant [8 x i8] c"Thread2\00", align 1
@.str2 = private unnamed_addr constant [22 x i8] c"Thread 1 returns: %d\0A\00", align 1
@.str3 = private unnamed_addr constant [22 x i8] c"Thread 2 returns: %d\0A\00", align 1
@.str4 = private unnamed_addr constant [24 x i8] c"Hello World! I am , %s\0A\00", align 1
@.str5 = private unnamed_addr constant [22 x i8] c"Bye World! I am , %s\0A\00", align 1

define i32 @main() nounwind {
entry:
  %retval = alloca i32
  %thread1 = alloca i64
  %thread2 = alloca i64
  %message1 = alloca i8*
  %message2 = alloca i8*
  %retval1 = alloca i32
  %retval2 = alloca i32
  %"alloca point" = bitcast i32 0 to i32
  store i8* getelementptr inbounds ([8 x i8]* @.str, i64 0, i64 0), i8** %message1, align 8
  store i8* getelementptr inbounds ([8 x i8]* @.str1, i64 0, i64 0), i8** %message2, align 8
  %0 = load i8** %message1, align 8
  %1 = call i32 @pthread_create(i64* noalias %thread1, %union.pthread_attr_t* noalias null, i8* (i8*)* @PrintHello, i8* noalias %0) nounwind
  store i32 %1, i32* %retval1, align 4
  %2 = load i8** %message2, align 8
  %3 = call i32 @pthread_create(i64* noalias %thread2, %union.pthread_attr_t* noalias null, i8* (i8*)* @PrintBye, i8* noalias %2) nounwind
  store i32 %3, i32* %retval2, align 4
  %4 = load i32* %retval1, align 4
  %5 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([22 x i8]* @.str2, i64 0, i64 0), i32 %4) nounwind
  %6 = load i32* %retval2, align 4
  %7 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([22 x i8]* @.str3, i64 0, i64 0), i32 %6) nounwind
  %8 = call i32 @pthread_mutex_lock(%union.pthread_mutex_t* @mutex1) nounwind
  %9 = load i64* %thread1, align 8
  %10 = call i32 @pthread_join(i64 %9, i8** null) nounwind
  %11 = load i64* %thread2, align 8
  %12 = call i32 @pthread_join(i64 %11, i8** null) nounwind
  call void @exit(i32 0) noreturn nounwind
  unreachable

return:                                           ; No predecessors!
  %retval3 = load i32* %retval
  ret i32 %retval3
}

declare i32 @pthread_create(i64* noalias, %union.pthread_attr_t* noalias, i8* (i8*)*, i8* noalias) nounwind

declare i32 @printf(i8* noalias, ...) nounwind

declare i32 @pthread_mutex_lock(%union.pthread_mutex_t*) nounwind

declare i32 @pthread_join(i64, i8**)

declare void @exit(i32) noreturn nounwind

define i8* @PrintHello(i8* %ptr) nounwind {
entry:
  %ptr_addr = alloca i8*, align 8
  %retval = alloca i8*
  %message = alloca i8*
  %"alloca point" = bitcast i32 0 to i32
  store i8* %ptr, i8** %ptr_addr
  %0 = load i8** %ptr_addr, align 8
  store i8* %0, i8** %message, align 8
  %1 = load i8** %message, align 8
  %2 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([24 x i8]* @.str4, i64 0, i64 0), i8* %1) nounwind
  br label %return

return:                                           ; preds = %entry
  %retval1 = load i8** %retval
  ret i8* %retval1
}

define i8* @PrintBye(i8* %ptr) nounwind {
entry:
  %ptr_addr = alloca i8*, align 8
  %retval = alloca i8*
  %message = alloca i8*
  %"alloca point" = bitcast i32 0 to i32
  store i8* %ptr, i8** %ptr_addr
  %0 = load i8** %ptr_addr, align 8
  store i8* %0, i8** %message, align 8
  %1 = load i8** %message, align 8
  %2 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([22 x i8]* @.str5, i64 0, i64 0), i8* %1) nounwind
  br label %return

return:                                           ; preds = %entry
  %retval1 = load i8** %retval
  ret i8* %retval1
}
