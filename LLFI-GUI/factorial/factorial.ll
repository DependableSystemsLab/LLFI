; ModuleID = '/ubc/ece/home/kp/grads/nithyan/Installer_Package/LLFI-Gui_v1.0_x86_64/llfisrc/LLFI-GUI/factorial/factorial.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main(i32 %argc, i8** %argv) #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i8**, align 8
  %i = alloca i32, align 4
  %fact = alloca i32, align 4
  %n = alloca i32, align 4
  store i32 0, i32* %1
  store i32 %argc, i32* %2, align 4
  store i8** %argv, i8*** %3, align 8
  %4 = load i8*** %3, align 8
  %5 = getelementptr inbounds i8** %4, i64 1
  %6 = load i8** %5, align 8
  %7 = call i32 (i8*, ...)* bitcast (i32 (...)* @atoi to i32 (i8*, ...)*)(i8* %6)
  store i32 %7, i32* %n, align 4
  store i32 1, i32* %fact, align 4
  store i32 1, i32* %i, align 4
  br label %8

; <label>:8                                       ; preds = %16, %0
  %9 = load i32* %i, align 4
  %10 = load i32* %n, align 4
  %11 = icmp sle i32 %9, %10
  br i1 %11, label %12, label %19

; <label>:12                                      ; preds = %8
  %13 = load i32* %fact, align 4
  %14 = load i32* %i, align 4
  %15 = mul nsw i32 %13, %14
  store i32 %15, i32* %fact, align 4
  br label %16

; <label>:16                                      ; preds = %12
  %17 = load i32* %i, align 4
  %18 = add nsw i32 %17, 1
  store i32 %18, i32* %i, align 4
  br label %8

; <label>:19                                      ; preds = %8
  %20 = load i32* %fact, align 4
  %21 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @.str, i32 0, i32 0), i32 %20)
  %22 = load i32* %1
  ret i32 %22
}

declare i32 @atoi(...) #1

declare i32 @printf(i8*, ...) #1

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf"="true" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf"="true" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "unsafe-fp-math"="false" "use-soft-float"="false" }
