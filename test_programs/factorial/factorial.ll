; ModuleID = '/ubc/ece/home/am/grads/raiyat/project/LLFI/test_programs/factorial/factorial.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-f128:128:128-n8:16:32:64"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define i32 @main(i32 %argc, i8** %argv) nounwind {
entry:
  %argc_addr = alloca i32, align 4
  %argv_addr = alloca i8**, align 8
  %retval = alloca i32
  %i = alloca i32
  %fact = alloca i32
  %n = alloca i32
  %buf = alloca i8*
  %"alloca point" = bitcast i32 0 to i32
  store i32 %argc, i32* %argc_addr
  store i8** %argv, i8*** %argv_addr
  %0 = load i8*** %argv_addr, align 8
  %1 = getelementptr inbounds i8** %0, i64 1
  %2 = load i8** %1, align 1
  %3 = call i32 (...)* @atoi(i8* %2) nounwind
  store i32 %3, i32* %n, align 4
  store i32 1, i32* %fact, align 4
  store i32 1, i32* %i, align 4
  br label %bb1

bb:                                               ; preds = %bb1
  %4 = load i32* %fact, align 4
  %5 = load i32* %i, align 4
  %6 = mul nsw i32 %4, %5
  store i32 %6, i32* %fact, align 4
  %7 = load i32* %i, align 4
  %8 = add nsw i32 %7, 1
  store i32 %8, i32* %i, align 4
  br label %bb1

bb1:                                              ; preds = %bb, %entry
  %9 = load i32* %i, align 4
  %10 = load i32* %n, align 4
  %11 = icmp sle i32 %9, %10
  br i1 %11, label %bb, label %bb2

bb2:                                              ; preds = %bb1
  %12 = load i32* %fact, align 4
  %13 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([4 x i8]* @.str, i64 0, i64 0), i32 %12) nounwind
  br label %return

return:                                           ; preds = %bb2
  %retval3 = load i32* %retval
  ret i32 %retval3
}

declare i32 @atoi(...)

declare i32 @printf(i8* noalias, ...) nounwind
