; ModuleID = '/ubc/ece/home/kp/grads/raiyat/newproject/LLFI-Cisco-master/test_programs/Mem-F1/memcpy2.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-f128:128:128-n8:16:32:64"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [27 x i8] c"Enter number of elements: \00", align 1
@.str1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str2 = private unnamed_addr constant [40 x i8] c"This is a fault injection experiment!! \00", align 8
@.str3 = private unnamed_addr constant [18 x i8] c" memcpy src = %s\0A\00", align 1
@.str4 = private unnamed_addr constant [25 x i8] c"Before memcpy dest = %s\0A\00", align 1
@.str5 = private unnamed_addr constant [24 x i8] c"After memcpy dest = %s\0A\00", align 1

define i32 @main() nounwind {
entry:
  %retval = alloca i32
  %0 = alloca i32
  %src = alloca i8*
  %n = alloca i32
  %size = alloca i32
  %dest = alloca i8*
  %i = alloca i32
  %"alloca point" = bitcast i32 0 to i32
  %1 = call noalias i8* @malloc(i64 40) nounwind
  store i8* %1, i8** %src, align 8
  %2 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([27 x i8]* @.str, i64 0, i64 0)) nounwind
  %3 = call i32 (i8*, ...)* @"\01__isoc99_scanf"(i8* noalias getelementptr inbounds ([3 x i8]* @.str1, i64 0, i64 0), i32* %n) nounwind
  %4 = load i32* %n, align 4
  store i32 %4, i32* %size, align 4
  %5 = load i32* %size, align 4
  %6 = sext i32 %5 to i64
  %7 = call noalias i8* @malloc(i64 %6) nounwind
  store i8* %7, i8** %dest, align 8
  store i8* getelementptr inbounds ([40 x i8]* @.str2, i64 0, i64 0), i8** %src, align 8
  %8 = load i8** %src, align 8
  %9 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([18 x i8]* @.str3, i64 0, i64 0), i8* %8) nounwind
  %10 = load i8** %dest, align 8
  %11 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([25 x i8]* @.str4, i64 0, i64 0), i8* %10) nounwind
  store i32 0, i32* %i, align 4
  br label %bb1

bb:                                               ; preds = %bb1
  %12 = load i8** %dest, align 8
  %13 = load i8** %src, align 8
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %12, i8* %13, i64 40, i32 1, i1 false)
  %14 = load i32* %i, align 4
  %15 = add nsw i32 %14, 1
  store i32 %15, i32* %i, align 4
  br label %bb1

bb1:                                              ; preds = %bb, %entry
  %16 = load i32* %i, align 4
  %17 = icmp sle i32 %16, 10
  br i1 %17, label %bb, label %bb2

bb2:                                              ; preds = %bb1
  %18 = load i8** %dest, align 8
  %19 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([24 x i8]* @.str5, i64 0, i64 0), i8* %18) nounwind
  store i32 0, i32* %0, align 4
  %20 = load i32* %0, align 4
  store i32 %20, i32* %retval, align 4
  br label %return

return:                                           ; preds = %bb2
  %retval3 = load i32* %retval
  ret i32 %retval3
}

declare noalias i8* @malloc(i64) nounwind

declare i32 @printf(i8* noalias, ...) nounwind

declare i32 @"\01__isoc99_scanf"(i8* noalias, ...) nounwind

declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture, i64, i32, i1) nounwind
