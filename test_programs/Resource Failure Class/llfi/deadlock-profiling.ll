; ModuleID = '/ubc/ece/home/kp/grads/raiyat/newproject/LLFI-Cisco-master/LLFI-GUI/deadlock/llfi/deadlock-llfi_index.ll'
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
  %retval = alloca i32, !llfi_index !0
  %thread1 = alloca i64, !llfi_index !1
  %thread2 = alloca i64, !llfi_index !2
  %message1 = alloca i8*, !llfi_index !3
  %message2 = alloca i8*, !llfi_index !4
  %retval1 = alloca i32, !llfi_index !5
  %retval2 = alloca i32, !llfi_index !6
  %"alloca point" = bitcast i32 0 to i32, !llfi_index !7
  store i8* getelementptr inbounds ([8 x i8]* @.str, i64 0, i64 0), i8** %message1, align 8, !llfi_index !8
  store i8* getelementptr inbounds ([8 x i8]* @.str1, i64 0, i64 0), i8** %message2, align 8, !llfi_index !9
  %0 = load i8** %message1, align 8, !llfi_index !10
  %1 = call i32 @pthread_create(i64* noalias %thread1, %union.pthread_attr_t* noalias null, i8* (i8*)* @PrintHello, i8* noalias %0) nounwind, !llfi_index !11
  store i32 %1, i32* %retval1, align 4, !llfi_index !12
  %2 = load i8** %message2, align 8, !llfi_index !13
  %3 = call i32 @pthread_create(i64* noalias %thread2, %union.pthread_attr_t* noalias null, i8* (i8*)* @PrintBye, i8* noalias %2) nounwind, !llfi_index !14
  store i32 %3, i32* %retval2, align 4, !llfi_index !15
  %4 = load i32* %retval1, align 4, !llfi_index !16
  %5 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([22 x i8]* @.str2, i64 0, i64 0), i32 %4) nounwind, !llfi_index !17
  %6 = load i32* %retval2, align 4, !llfi_index !18
  %7 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([22 x i8]* @.str3, i64 0, i64 0), i32 %6) nounwind, !llfi_index !19
  %8 = call i32 @pthread_mutex_lock(%union.pthread_mutex_t* @mutex1) nounwind, !llfi_index !20
  %9 = load i64* %thread1, align 8, !llfi_index !21
  call void @doProfiling(i32 45)
  %10 = call i32 @pthread_join(i64 %9, i8** null) nounwind, !llfi_index !22
  %11 = load i64* %thread2, align 8, !llfi_index !23
  call void @doProfiling(i32 45)
  %12 = call i32 @pthread_join(i64 %11, i8** null) nounwind, !llfi_index !24
  call void @endProfiling()
  call void @exit(i32 0) noreturn nounwind, !llfi_index !25
  unreachable, !llfi_index !26

return:                                           ; No predecessors!
  %retval3 = load i32* %retval, !llfi_index !27
  call void @endProfiling()
  ret i32 %retval3, !llfi_index !28
}

declare i32 @pthread_create(i64* noalias, %union.pthread_attr_t* noalias, i8* (i8*)*, i8* noalias) nounwind

declare i32 @printf(i8* noalias, ...) nounwind

declare i32 @pthread_mutex_lock(%union.pthread_mutex_t*) nounwind

declare i32 @pthread_join(i64, i8**)

declare void @exit(i32) noreturn nounwind

define i8* @PrintHello(i8* %ptr) nounwind {
entry:
  %ptr_addr = alloca i8*, align 8, !llfi_index !29
  %retval = alloca i8*, !llfi_index !30
  %message = alloca i8*, !llfi_index !31
  %"alloca point" = bitcast i32 0 to i32, !llfi_index !32
  store i8* %ptr, i8** %ptr_addr, !llfi_index !33
  %0 = load i8** %ptr_addr, align 8, !llfi_index !34
  store i8* %0, i8** %message, align 8, !llfi_index !35
  %1 = load i8** %message, align 8, !llfi_index !36
  %2 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([24 x i8]* @.str4, i64 0, i64 0), i8* %1) nounwind, !llfi_index !37
  br label %return, !llfi_index !38

return:                                           ; preds = %entry
  %retval1 = load i8** %retval, !llfi_index !39
  ret i8* %retval1, !llfi_index !40
}

define i8* @PrintBye(i8* %ptr) nounwind {
entry:
  %ptr_addr = alloca i8*, align 8, !llfi_index !41
  %retval = alloca i8*, !llfi_index !42
  %message = alloca i8*, !llfi_index !43
  %"alloca point" = bitcast i32 0 to i32, !llfi_index !44
  store i8* %ptr, i8** %ptr_addr, !llfi_index !45
  %0 = load i8** %ptr_addr, align 8, !llfi_index !46
  store i8* %0, i8** %message, align 8, !llfi_index !47
  %1 = load i8** %message, align 8, !llfi_index !48
  %2 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([22 x i8]* @.str5, i64 0, i64 0), i8* %1) nounwind, !llfi_index !49
  br label %return, !llfi_index !50

return:                                           ; preds = %entry
  %retval1 = load i8** %retval, !llfi_index !51
  ret i8* %retval1, !llfi_index !52
}

declare void @doProfiling(i32)

declare void @endProfiling()

!0 = metadata !{i64 0}
!1 = metadata !{i64 1}
!2 = metadata !{i64 2}
!3 = metadata !{i64 3}
!4 = metadata !{i64 4}
!5 = metadata !{i64 5}
!6 = metadata !{i64 6}
!7 = metadata !{i64 7}
!8 = metadata !{i64 8}
!9 = metadata !{i64 9}
!10 = metadata !{i64 10}
!11 = metadata !{i64 11}
!12 = metadata !{i64 12}
!13 = metadata !{i64 13}
!14 = metadata !{i64 14}
!15 = metadata !{i64 15}
!16 = metadata !{i64 16}
!17 = metadata !{i64 17}
!18 = metadata !{i64 18}
!19 = metadata !{i64 19}
!20 = metadata !{i64 20}
!21 = metadata !{i64 21}
!22 = metadata !{i64 22}
!23 = metadata !{i64 23}
!24 = metadata !{i64 24}
!25 = metadata !{i64 25}
!26 = metadata !{i64 26}
!27 = metadata !{i64 27}
!28 = metadata !{i64 28}
!29 = metadata !{i64 29}
!30 = metadata !{i64 30}
!31 = metadata !{i64 31}
!32 = metadata !{i64 32}
!33 = metadata !{i64 33}
!34 = metadata !{i64 34}
!35 = metadata !{i64 35}
!36 = metadata !{i64 36}
!37 = metadata !{i64 37}
!38 = metadata !{i64 38}
!39 = metadata !{i64 39}
!40 = metadata !{i64 40}
!41 = metadata !{i64 41}
!42 = metadata !{i64 42}
!43 = metadata !{i64 43}
!44 = metadata !{i64 44}
!45 = metadata !{i64 45}
!46 = metadata !{i64 46}
!47 = metadata !{i64 47}
!48 = metadata !{i64 48}
!49 = metadata !{i64 49}
!50 = metadata !{i64 50}
!51 = metadata !{i64 51}
!52 = metadata !{i64 52}
