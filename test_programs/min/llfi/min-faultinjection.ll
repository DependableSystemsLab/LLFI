; ModuleID = '/ubc/ece/home/am/grads/raiyat/project/LLFI/test_programs/min/llfi/min-llfi_index.ll'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-f128:128:128-n8:16:32:64"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [10 x i8] c"Min is:%d\00", align 1

define i32 @main(i32 %argc, i8** %argv) nounwind {
entry:
  call void @initInjections()
  %argc_addr = alloca i32, align 4, !llfi_index !0
  %fi1 = call i32* @injectFault1(i64 0, i32* %argc_addr, i32 26, i32 0, i32 1)
  %argv_addr = alloca i8**, align 8, !llfi_index !1
  %fi = call i8*** @injectFault0(i64 1, i8*** %argv_addr, i32 26, i32 0, i32 1)
  %retval = alloca i32, !llfi_index !2
  %fi7 = call i32* @injectFault1(i64 2, i32* %retval, i32 26, i32 0, i32 1)
  %0 = alloca i32, !llfi_index !3
  %fi8 = call i32* @injectFault1(i64 3, i32* %0, i32 26, i32 0, i32 1)
  %arr = alloca [5 x i32], !llfi_index !4
  %fi9 = call [5 x i32]* @injectFault4(i64 4, [5 x i32]* %arr, i32 26, i32 0, i32 1)
  %min = alloca i32, !llfi_index !5
  %fi10 = call i32* @injectFault1(i64 5, i32* %min, i32 26, i32 0, i32 1)
  %i = alloca i32, !llfi_index !6
  %fi11 = call i32* @injectFault1(i64 6, i32* %i, i32 26, i32 0, i32 1)
  %"alloca point" = bitcast i32 0 to i32, !llfi_index !7
  %fi12 = call i32 @injectFault2(i64 7, i32 %"alloca point", i32 41, i32 0, i32 1)
  store i32 %argc, i32* %fi1, !llfi_index !8
  store i8** %argv, i8*** %fi, !llfi_index !9
  store i32 0, i32* %fi11, align 4, !llfi_index !10
  br label %bb1, !llfi_index !11

bb:                                               ; preds = %bb1
  %1 = load i32* %fi11, align 4, !llfi_index !12
  %fi13 = call i32 @injectFault2(i64 12, i32 %1, i32 27, i32 0, i32 1)
  %2 = load i32* %fi11, align 4, !llfi_index !13
  %fi14 = call i32 @injectFault2(i64 13, i32 %2, i32 27, i32 0, i32 1)
  %3 = add nsw i32 %fi14, 1, !llfi_index !14
  %fi15 = call i32 @injectFault2(i64 14, i32 %3, i32 8, i32 0, i32 1)
  %4 = load i8*** %fi, align 8, !llfi_index !15
  %fi16 = call i8** @injectFault5(i64 15, i8** %4, i32 27, i32 0, i32 1)
  %5 = sext i32 %fi15 to i64, !llfi_index !16
  %fi17 = call i64 @injectFault6(i64 16, i64 %5, i32 32, i32 0, i32 1)
  %6 = getelementptr inbounds i8** %fi16, i64 %fi17, !llfi_index !17
  %fi18 = call i8** @injectFault5(i64 17, i8** %6, i32 29, i32 0, i32 1)
  %7 = load i8** %fi18, align 1, !llfi_index !18
  %fi19 = call i8* @injectFault7(i64 18, i8* %7, i32 27, i32 0, i32 1)
  %8 = call i32 (...)* @atoi(i8* %fi19) nounwind, !llfi_index !19
  %fi20 = call i32 @injectFault2(i64 19, i32 %8, i32 45, i32 0, i32 1)
  %9 = sext i32 %fi13 to i64, !llfi_index !20
  %fi21 = call i64 @injectFault6(i64 20, i64 %9, i32 32, i32 0, i32 1)
  %10 = getelementptr inbounds [5 x i32]* %fi9, i64 0, i64 %fi21, !llfi_index !21
  %fi22 = call i32* @injectFault1(i64 21, i32* %10, i32 29, i32 0, i32 1)
  store i32 %fi20, i32* %fi22, align 4, !llfi_index !22
  %11 = load i32* %fi11, align 4, !llfi_index !23
  %fi23 = call i32 @injectFault2(i64 23, i32 %11, i32 27, i32 0, i32 1)
  %12 = add nsw i32 %fi23, 1, !llfi_index !24
  %fi24 = call i32 @injectFault2(i64 24, i32 %12, i32 8, i32 0, i32 1)
  store i32 %fi24, i32* %fi11, align 4, !llfi_index !25
  br label %bb1, !llfi_index !26

bb1:                                              ; preds = %bb, %entry
  %13 = load i32* %fi11, align 4, !llfi_index !27
  %fi25 = call i32 @injectFault2(i64 27, i32 %13, i32 27, i32 0, i32 1)
  %14 = icmp sle i32 %fi25, 4, !llfi_index !28
  %fi26 = call i1 @injectFault3(i64 28, i1 %14, i32 42, i32 0, i32 1)
  br i1 %fi26, label %bb, label %bb2, !llfi_index !29

bb2:                                              ; preds = %bb1
  %15 = getelementptr inbounds [5 x i32]* %fi9, i64 0, i64 0, !llfi_index !30
  %fi27 = call i32* @injectFault1(i64 30, i32* %15, i32 29, i32 0, i32 1)
  %16 = load i32* %fi27, align 4, !llfi_index !31
  %fi28 = call i32 @injectFault2(i64 31, i32 %16, i32 27, i32 0, i32 1)
  store i32 %fi28, i32* %fi10, align 4, !llfi_index !32
  store i32 1, i32* %fi11, align 4, !llfi_index !33
  br label %bb6, !llfi_index !34

bb3:                                              ; preds = %bb6
  %17 = load i32* %fi11, align 4, !llfi_index !35
  %fi30 = call i32 @injectFault2(i64 35, i32 %17, i32 27, i32 0, i32 1)
  %18 = sext i32 %fi30 to i64, !llfi_index !36
  %fi31 = call i64 @injectFault6(i64 36, i64 %18, i32 32, i32 0, i32 1)
  %19 = getelementptr inbounds [5 x i32]* %fi9, i64 0, i64 %fi31, !llfi_index !37
  %fi32 = call i32* @injectFault1(i64 37, i32* %19, i32 29, i32 0, i32 1)
  %20 = load i32* %fi32, align 4, !llfi_index !38
  %fi33 = call i32 @injectFault2(i64 38, i32 %20, i32 27, i32 0, i32 1)
  %21 = load i32* %fi10, align 4, !llfi_index !39
  %fi34 = call i32 @injectFault2(i64 39, i32 %21, i32 27, i32 0, i32 1)
  %22 = icmp slt i32 %fi33, %fi34, !llfi_index !40
  %fi35 = call i1 @injectFault3(i64 40, i1 %22, i32 42, i32 0, i32 1)
  br i1 %fi35, label %bb4, label %bb5, !llfi_index !41

bb4:                                              ; preds = %bb3
  %23 = load i32* %fi11, align 4, !llfi_index !42
  %fi36 = call i32 @injectFault2(i64 42, i32 %23, i32 27, i32 0, i32 1)
  %24 = sext i32 %fi36 to i64, !llfi_index !43
  %fi37 = call i64 @injectFault6(i64 43, i64 %24, i32 32, i32 0, i32 1)
  %25 = getelementptr inbounds [5 x i32]* %fi9, i64 0, i64 %fi37, !llfi_index !44
  %fi38 = call i32* @injectFault1(i64 44, i32* %25, i32 29, i32 0, i32 1)
  %26 = load i32* %fi38, align 4, !llfi_index !45
  %fi39 = call i32 @injectFault2(i64 45, i32 %26, i32 27, i32 0, i32 1)
  store i32 %fi39, i32* %fi10, align 4, !llfi_index !46
  br label %bb5, !llfi_index !47

bb5:                                              ; preds = %bb4, %bb3
  %27 = load i32* %fi11, align 4, !llfi_index !48
  %fi2 = call i32 @injectFault2(i64 48, i32 %27, i32 27, i32 0, i32 1)
  %28 = add nsw i32 %fi2, 1, !llfi_index !49
  %fi3 = call i32 @injectFault2(i64 49, i32 %28, i32 8, i32 0, i32 1)
  store i32 %fi3, i32* %fi11, align 4, !llfi_index !50
  br label %bb6, !llfi_index !51

bb6:                                              ; preds = %bb5, %bb2
  %29 = load i32* %fi11, align 4, !llfi_index !52
  %fi4 = call i32 @injectFault2(i64 52, i32 %29, i32 27, i32 0, i32 1)
  %30 = icmp sle i32 %fi4, 4, !llfi_index !53
  %fi5 = call i1 @injectFault3(i64 53, i1 %30, i32 42, i32 0, i32 1)
  br i1 %fi5, label %bb3, label %bb7, !llfi_index !54

bb7:                                              ; preds = %bb6
  %31 = load i32* %fi10, align 4, !llfi_index !55
  %fi6 = call i32 @injectFault2(i64 55, i32 %31, i32 27, i32 0, i32 1)
  %32 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([10 x i8]* @.str, i64 0, i64 0), i32 %fi6) nounwind, !llfi_index !56
  %fi40 = call i32 @injectFault2(i64 56, i32 %32, i32 45, i32 0, i32 1)
  store i32 0, i32* %fi8, align 4, !llfi_index !57
  %33 = load i32* %fi8, align 4, !llfi_index !58
  %fi29 = call i32 @injectFault2(i64 58, i32 %33, i32 27, i32 0, i32 1)
  store i32 %fi29, i32* %fi7, align 4, !llfi_index !59
  br label %return, !llfi_index !60

return:                                           ; preds = %bb7
  %retval8 = load i32* %fi7, !llfi_index !61
  %fi41 = call i32 @injectFault2(i64 61, i32 %retval8, i32 27, i32 0, i32 1)
  call void @postInjections()
  ret i32 %fi41, !llfi_index !62
}

declare i32 @atoi(...)

declare i32 @printf(i8* noalias, ...) nounwind

define i8*** @injectFault0(i64, i8***, i32, i32, i32) {
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

define i32* @injectFault1(i64, i32*, i32, i32, i32) {
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

define i32 @injectFault2(i64, i32, i32, i32, i32) {
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

define i1 @injectFault3(i64, i1, i32, i32, i32) {
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

define [5 x i32]* @injectFault4(i64, [5 x i32]*, i32, i32, i32) {
entry:
  %tmploc = alloca [5 x i32]*
  store [5 x i32]* %1, [5 x i32]** %tmploc
  %pre_cond = call i1 @preFunc(i64 %0, i32 %2, i32 %3, i32 %4)
  br i1 %pre_cond, label %inject, label %exit

inject:                                           ; preds = %entry
  %tmploc_cast = bitcast [5 x i32]** %tmploc to i8*
  call void @injectFunc(i64 %0, i32 64, i8* %tmploc_cast, i32 %3)
  br label %exit

exit:                                             ; preds = %inject, %entry
  %updateval = load [5 x i32]** %tmploc
  ret [5 x i32]* %updateval
}

define i8** @injectFault5(i64, i8**, i32, i32, i32) {
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

define i64 @injectFault6(i64, i64, i32, i32, i32) {
entry:
  %tmploc = alloca i64
  store i64 %1, i64* %tmploc
  %pre_cond = call i1 @preFunc(i64 %0, i32 %2, i32 %3, i32 %4)
  br i1 %pre_cond, label %inject, label %exit

inject:                                           ; preds = %entry
  %tmploc_cast = bitcast i64* %tmploc to i8*
  call void @injectFunc(i64 %0, i32 64, i8* %tmploc_cast, i32 %3)
  br label %exit

exit:                                             ; preds = %inject, %entry
  %updateval = load i64* %tmploc
  ret i64 %updateval
}

define i8* @injectFault7(i64, i8*, i32, i32, i32) {
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

declare void @initInjections()

declare void @postInjections()

declare i1 @preFunc(i64, i32, i32, i32)

declare void @injectFunc(i64, i32, i8*, i32)

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
!53 = metadata !{i64 53}
!54 = metadata !{i64 54}
!55 = metadata !{i64 55}
!56 = metadata !{i64 56}
!57 = metadata !{i64 57}
!58 = metadata !{i64 58}
!59 = metadata !{i64 59}
!60 = metadata !{i64 60}
!61 = metadata !{i64 61}
!62 = metadata !{i64 62}
