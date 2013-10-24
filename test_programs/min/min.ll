; ModuleID = '/ubc/ece/home/am/grads/raiyat/project/LLFI/test_programs/min/min.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-f128:128:128-n8:16:32:64"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [10 x i8] c"Min is:%d\00", align 1

define i32 @main(i32 %argc, i8** %argv) nounwind {
entry:
  %argc_addr = alloca i32, align 4
  %argv_addr = alloca i8**, align 8
  %retval = alloca i32
  %0 = alloca i32
  %arr = alloca [5 x i32]
  %min = alloca i32
  %i = alloca i32
  %"alloca point" = bitcast i32 0 to i32
  store i32 %argc, i32* %argc_addr
  store i8** %argv, i8*** %argv_addr
  store i32 0, i32* %i, align 4
  br label %bb1

bb:                                               ; preds = %bb1
  %1 = load i32* %i, align 4
  %2 = load i32* %i, align 4
  %3 = add nsw i32 %2, 1
  %4 = load i8*** %argv_addr, align 8
  %5 = sext i32 %3 to i64
  %6 = getelementptr inbounds i8** %4, i64 %5
  %7 = load i8** %6, align 1
  %8 = call i32 (...)* @atoi(i8* %7) nounwind
  %9 = sext i32 %1 to i64
  %10 = getelementptr inbounds [5 x i32]* %arr, i64 0, i64 %9
  store i32 %8, i32* %10, align 4
  %11 = load i32* %i, align 4
  %12 = add nsw i32 %11, 1
  store i32 %12, i32* %i, align 4
  br label %bb1

bb1:                                              ; preds = %bb, %entry
  %13 = load i32* %i, align 4
  %14 = icmp sle i32 %13, 4
  br i1 %14, label %bb, label %bb2

bb2:                                              ; preds = %bb1
  %15 = getelementptr inbounds [5 x i32]* %arr, i64 0, i64 0
  %16 = load i32* %15, align 4
  store i32 %16, i32* %min, align 4
  store i32 1, i32* %i, align 4
  br label %bb6

bb3:                                              ; preds = %bb6
  %17 = load i32* %i, align 4
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds [5 x i32]* %arr, i64 0, i64 %18
  %20 = load i32* %19, align 4
  %21 = load i32* %min, align 4
  %22 = icmp slt i32 %20, %21
  br i1 %22, label %bb4, label %bb5

bb4:                                              ; preds = %bb3
  %23 = load i32* %i, align 4
  %24 = sext i32 %23 to i64
  %25 = getelementptr inbounds [5 x i32]* %arr, i64 0, i64 %24
  %26 = load i32* %25, align 4
  store i32 %26, i32* %min, align 4
  br label %bb5

bb5:                                              ; preds = %bb4, %bb3
  %27 = load i32* %i, align 4
  %28 = add nsw i32 %27, 1
  store i32 %28, i32* %i, align 4
  br label %bb6

bb6:                                              ; preds = %bb5, %bb2
  %29 = load i32* %i, align 4
  %30 = icmp sle i32 %29, 4
  br i1 %30, label %bb3, label %bb7

bb7:                                              ; preds = %bb6
  %31 = load i32* %min, align 4
  %32 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([10 x i8]* @.str, i64 0, i64 0), i32 %31) nounwind
  store i32 0, i32* %0, align 4
  %33 = load i32* %0, align 4
  store i32 %33, i32* %retval, align 4
  br label %return

return:                                           ; preds = %bb7
  %retval8 = load i32* %retval
  ret i32 %retval8
}

declare i32 @atoi(...)

declare i32 @printf(i8* noalias, ...) nounwind
