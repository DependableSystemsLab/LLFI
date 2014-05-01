; ModuleID = '/ubc/ece/home/kp/grads/nithyan/Installer_Package/LLFI-Gui_v1.0_x86_64/llfisrc/LLFI-GUI/factorial/llfi/factorial-llfi_index.ll'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main(i32 %argc, i8** %argv) #0 {
  %1 = alloca i32, align 4, !llfi_index !0
  call void @doProfiling(i32 26)
  %2 = alloca i32, align 4, !llfi_index !1
  call void @doProfiling(i32 26)
  %3 = alloca i8**, align 8, !llfi_index !2
  call void @doProfiling(i32 26)
  %i = alloca i32, align 4, !llfi_index !3
  call void @doProfiling(i32 26)
  %fact = alloca i32, align 4, !llfi_index !4
  call void @doProfiling(i32 26)
  %n = alloca i32, align 4, !llfi_index !5
  call void @doProfiling(i32 26)
  store i32 0, i32* %1, !llfi_index !6
  store i32 %argc, i32* %2, align 4, !llfi_index !7
  store i8** %argv, i8*** %3, align 8, !llfi_index !8
  %4 = load i8*** %3, align 8, !llfi_index !9
  call void @doProfiling(i32 27)
  %5 = getelementptr inbounds i8** %4, i64 1, !llfi_index !10
  call void @doProfiling(i32 29)
  %6 = load i8** %5, align 8, !llfi_index !11
  call void @doProfiling(i32 27)
  %7 = call i32 (i8*, ...)* bitcast (i32 (...)* @atoi to i32 (i8*, ...)*)(i8* %6), !llfi_index !12
  call void @doProfiling(i32 48)
  store i32 %7, i32* %n, align 4, !llfi_index !13
  store i32 1, i32* %fact, align 4, !llfi_index !14
  store i32 1, i32* %i, align 4, !llfi_index !15
  br label %8, !llfi_index !16

; <label>:8                                       ; preds = %16, %0
  %9 = load i32* %i, align 4, !llfi_index !17
  call void @doProfiling(i32 27)
  %10 = load i32* %n, align 4, !llfi_index !18
  call void @doProfiling(i32 27)
  %11 = icmp sle i32 %9, %10, !llfi_index !19
  call void @doProfiling(i32 45)
  br i1 %11, label %12, label %19, !llfi_index !20

; <label>:12                                      ; preds = %8
  %13 = load i32* %fact, align 4, !llfi_index !21
  call void @doProfiling(i32 27)
  %14 = load i32* %i, align 4, !llfi_index !22
  call void @doProfiling(i32 27)
  %15 = mul nsw i32 %13, %14, !llfi_index !23
  call void @doProfiling(i32 12)
  store i32 %15, i32* %fact, align 4, !llfi_index !24
  br label %16, !llfi_index !25

; <label>:16                                      ; preds = %12
  %17 = load i32* %i, align 4, !llfi_index !26
  call void @doProfiling(i32 27)
  %18 = add nsw i32 %17, 1, !llfi_index !27
  call void @doProfiling(i32 8)
  store i32 %18, i32* %i, align 4, !llfi_index !28
  br label %8, !llfi_index !29

; <label>:19                                      ; preds = %8
  %20 = load i32* %fact, align 4, !llfi_index !30
  call void @doProfiling(i32 27)
  %21 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @.str, i32 0, i32 0), i32 %20), !llfi_index !31
  call void @doProfiling(i32 48)
  %22 = load i32* %1, !llfi_index !32
  call void @doProfiling(i32 27)
  call void @endProfiling()
  ret i32 %22, !llfi_index !33
}

declare i32 @atoi(...) #1

declare i32 @printf(i8*, ...) #1

declare void @doProfiling(i32)

declare void @endProfiling()

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf"="true" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf"="true" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "unsafe-fp-math"="false" "use-soft-float"="false" }

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
