; ModuleID = '/ubc/ece/home/kp/grads/nithyan/Installer_Package/LLFI-Gui_v1.0_x86_64/llfisrc/LLFI-GUI/factorial/llfi/factorial-llfi_index.ll'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main(i32 %argc, i8** %argv) #0 {
  call void @initInjections()
  %1 = alloca i32, align 4, !llfi_index !0
  %fi = call i32* @injectFault0(i64 0, i32* %1, i32 26, i32 0, i32 1)
  %2 = alloca i32, align 4, !llfi_index !1
  %fi1 = call i32* @injectFault0(i64 1, i32* %2, i32 26, i32 0, i32 1)
  %3 = alloca i8**, align 8, !llfi_index !2
  %fi2 = call i8*** @injectFault1(i64 2, i8*** %3, i32 26, i32 0, i32 1)
  %i = alloca i32, align 4, !llfi_index !3
  %fi3 = call i32* @injectFault0(i64 3, i32* %i, i32 26, i32 0, i32 1)
  %fact = alloca i32, align 4, !llfi_index !4
  %fi4 = call i32* @injectFault0(i64 4, i32* %fact, i32 26, i32 0, i32 1)
  %n = alloca i32, align 4, !llfi_index !5
  %fi5 = call i32* @injectFault0(i64 5, i32* %n, i32 26, i32 0, i32 1)
  store i32 0, i32* %fi, !llfi_index !6
  store i32 %argc, i32* %fi1, align 4, !llfi_index !7
  store i8** %argv, i8*** %fi2, align 8, !llfi_index !8
  %4 = load i8*** %fi2, align 8, !llfi_index !9
  %fi6 = call i8** @injectFault2(i64 9, i8** %4, i32 27, i32 0, i32 1)
  %5 = getelementptr inbounds i8** %fi6, i64 1, !llfi_index !10
  %fi7 = call i8** @injectFault2(i64 10, i8** %5, i32 29, i32 0, i32 1)
  %6 = load i8** %fi7, align 8, !llfi_index !11
  %fi8 = call i8* @injectFault3(i64 11, i8* %6, i32 27, i32 0, i32 1)
  %7 = call i32 (i8*, ...)* bitcast (i32 (...)* @atoi to i32 (i8*, ...)*)(i8* %fi8), !llfi_index !12
  %fi9 = call i32 @injectFault4(i64 12, i32 %7, i32 48, i32 0, i32 1)
  store i32 %fi9, i32* %fi5, align 4, !llfi_index !13
  store i32 1, i32* %fi4, align 4, !llfi_index !14
  store i32 1, i32* %fi3, align 4, !llfi_index !15
  br label %8, !llfi_index !16

; <label>:8                                       ; preds = %16, %0
  %9 = load i32* %fi3, align 4, !llfi_index !17
  %fi11 = call i32 @injectFault4(i64 17, i32 %9, i32 27, i32 0, i32 1)
  %10 = load i32* %fi5, align 4, !llfi_index !18
  %fi12 = call i32 @injectFault4(i64 18, i32 %10, i32 27, i32 0, i32 1)
  %11 = icmp sle i32 %fi11, %fi12, !llfi_index !19
  %fi13 = call i1 @injectFault5(i64 19, i1 %11, i32 45, i32 0, i32 1)
  br i1 %fi13, label %12, label %19, !llfi_index !20

; <label>:12                                      ; preds = %8
  %13 = load i32* %fi4, align 4, !llfi_index !21
  %fi14 = call i32 @injectFault4(i64 21, i32 %13, i32 27, i32 0, i32 1)
  %14 = load i32* %fi3, align 4, !llfi_index !22
  %fi15 = call i32 @injectFault4(i64 22, i32 %14, i32 27, i32 0, i32 1)
  %15 = mul nsw i32 %fi14, %fi15, !llfi_index !23
  %fi16 = call i32 @injectFault4(i64 23, i32 %15, i32 12, i32 0, i32 1)
  store i32 %fi16, i32* %fi4, align 4, !llfi_index !24
  br label %16, !llfi_index !25

; <label>:16                                      ; preds = %12
  %17 = load i32* %fi3, align 4, !llfi_index !26
  %fi10 = call i32 @injectFault4(i64 26, i32 %17, i32 27, i32 0, i32 1)
  %18 = add nsw i32 %fi10, 1, !llfi_index !27
  %fi17 = call i32 @injectFault4(i64 27, i32 %18, i32 8, i32 0, i32 1)
  store i32 %fi17, i32* %fi3, align 4, !llfi_index !28
  br label %8, !llfi_index !29

; <label>:19                                      ; preds = %8
  %20 = load i32* %fi4, align 4, !llfi_index !30
  %fi18 = call i32 @injectFault4(i64 30, i32 %20, i32 27, i32 0, i32 1)
  %21 = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @.str, i32 0, i32 0), i32 %fi18), !llfi_index !31
  %fi19 = call i32 @injectFault4(i64 31, i32 %21, i32 48, i32 0, i32 1)
  %22 = load i32* %fi, !llfi_index !32
  %fi20 = call i32 @injectFault4(i64 32, i32 %22, i32 27, i32 0, i32 1)
  call void @postInjections()
  ret i32 %fi20, !llfi_index !33
}

declare i32 @atoi(...) #1

declare i32 @printf(i8*, ...) #1

define i32* @injectFault0(i64, i32*, i32, i32, i32) {
entry:
  %tmploc = alloca i32*
  store i32* %1, i32** %tmploc
  %pre_cond = call i1 @preFunc(i64 %0, i32 %2, i32 %3, i32 %4)
  br i1 %pre_cond, label %inject, label %exit

inject:                                           ; preds = %entry
  %tmploc_cast = bitcast i32** %tmploc to i8*
  call void @injectFunc(i64 %0, i32 64, i8* %tmploc_cast, i32 %3)
  br label %exit

exit:                                             ; preds = %inject, %entry
  %updateval = load i32** %tmploc
  ret i32* %updateval
}

define i8*** @injectFault1(i64, i8***, i32, i32, i32) {
entry:
  %tmploc = alloca i8***
  store i8*** %1, i8**** %tmploc
  %pre_cond = call i1 @preFunc(i64 %0, i32 %2, i32 %3, i32 %4)
  br i1 %pre_cond, label %inject, label %exit

inject:                                           ; preds = %entry
  %tmploc_cast = bitcast i8**** %tmploc to i8*
  call void @injectFunc(i64 %0, i32 64, i8* %tmploc_cast, i32 %3)
  br label %exit

exit:                                             ; preds = %inject, %entry
  %updateval = load i8**** %tmploc
  ret i8*** %updateval
}

define i8** @injectFault2(i64, i8**, i32, i32, i32) {
entry:
  %tmploc = alloca i8**
  store i8** %1, i8*** %tmploc
  %pre_cond = call i1 @preFunc(i64 %0, i32 %2, i32 %3, i32 %4)
  br i1 %pre_cond, label %inject, label %exit

inject:                                           ; preds = %entry
  %tmploc_cast = bitcast i8*** %tmploc to i8*
  call void @injectFunc(i64 %0, i32 64, i8* %tmploc_cast, i32 %3)
  br label %exit

exit:                                             ; preds = %inject, %entry
  %updateval = load i8*** %tmploc
  ret i8** %updateval
}

define i8* @injectFault3(i64, i8*, i32, i32, i32) {
entry:
  %tmploc = alloca i8*
  store i8* %1, i8** %tmploc
  %pre_cond = call i1 @preFunc(i64 %0, i32 %2, i32 %3, i32 %4)
  br i1 %pre_cond, label %inject, label %exit

inject:                                           ; preds = %entry
  %tmploc_cast = bitcast i8** %tmploc to i8*
  call void @injectFunc(i64 %0, i32 64, i8* %tmploc_cast, i32 %3)
  br label %exit

exit:                                             ; preds = %inject, %entry
  %updateval = load i8** %tmploc
  ret i8* %updateval
}

define i32 @injectFault4(i64, i32, i32, i32, i32) {
entry:
  %tmploc = alloca i32
  store i32 %1, i32* %tmploc
  %pre_cond = call i1 @preFunc(i64 %0, i32 %2, i32 %3, i32 %4)
  br i1 %pre_cond, label %inject, label %exit

inject:                                           ; preds = %entry
  %tmploc_cast = bitcast i32* %tmploc to i8*
  call void @injectFunc(i64 %0, i32 32, i8* %tmploc_cast, i32 %3)
  br label %exit

exit:                                             ; preds = %inject, %entry
  %updateval = load i32* %tmploc
  ret i32 %updateval
}

define i1 @injectFault5(i64, i1, i32, i32, i32) {
entry:
  %tmploc = alloca i1
  store i1 %1, i1* %tmploc
  %pre_cond = call i1 @preFunc(i64 %0, i32 %2, i32 %3, i32 %4)
  br i1 %pre_cond, label %inject, label %exit

inject:                                           ; preds = %entry
  %tmploc_cast = bitcast i1* %tmploc to i8*
  call void @injectFunc(i64 %0, i32 1, i8* %tmploc_cast, i32 %3)
  br label %exit

exit:                                             ; preds = %inject, %entry
  %updateval = load i1* %tmploc
  ret i1 %updateval
}

declare void @initInjections()

declare void @postInjections()

declare i1 @preFunc(i64, i32, i32, i32)

declare void @injectFunc(i64, i32, i8*, i32)

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
