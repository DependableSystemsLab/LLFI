; ModuleID = '/ubc/ece/home/am/grads/raiyat/project/LLFI/test_programs/min/llfi/min-llfi_index.ll'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-f128:128:128-n8:16:32:64"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [10 x i8] c"Min is:%d\00", align 1

define i32 @main(i32 %argc, i8** %argv) nounwind {
entry:
  %argc_addr = alloca i32, align 4, !llfi_index !0
  call void @doProfiling(i32 26)
  %argv_addr = alloca i8**, align 8, !llfi_index !1
  call void @doProfiling(i32 26)
  %retval = alloca i32, !llfi_index !2
  call void @doProfiling(i32 26)
  %0 = alloca i32, !llfi_index !3
  call void @doProfiling(i32 26)
  %arr = alloca [5 x i32], !llfi_index !4
  call void @doProfiling(i32 26)
  %min = alloca i32, !llfi_index !5
  call void @doProfiling(i32 26)
  %i = alloca i32, !llfi_index !6
  call void @doProfiling(i32 26)
  %"alloca point" = bitcast i32 0 to i32, !llfi_index !7
  call void @doProfiling(i32 41)
  store i32 %argc, i32* %argc_addr, !llfi_index !8
  store i8** %argv, i8*** %argv_addr, !llfi_index !9
  store i32 0, i32* %i, align 4, !llfi_index !10
  br label %bb1, !llfi_index !11

bb:                                               ; preds = %bb1
  %1 = load i32* %i, align 4, !llfi_index !12
  call void @doProfiling(i32 27)
  %2 = load i32* %i, align 4, !llfi_index !13
  call void @doProfiling(i32 27)
  %3 = add nsw i32 %2, 1, !llfi_index !14
  call void @doProfiling(i32 8)
  %4 = load i8*** %argv_addr, align 8, !llfi_index !15
  call void @doProfiling(i32 27)
  %5 = sext i32 %3 to i64, !llfi_index !16
  call void @doProfiling(i32 32)
  %6 = getelementptr inbounds i8** %4, i64 %5, !llfi_index !17
  call void @doProfiling(i32 29)
  %7 = load i8** %6, align 1, !llfi_index !18
  call void @doProfiling(i32 27)
  %8 = call i32 (...)* @atoi(i8* %7) nounwind, !llfi_index !19
  call void @doProfiling(i32 45)
  %9 = sext i32 %1 to i64, !llfi_index !20
  call void @doProfiling(i32 32)
  %10 = getelementptr inbounds [5 x i32]* %arr, i64 0, i64 %9, !llfi_index !21
  call void @doProfiling(i32 29)
  store i32 %8, i32* %10, align 4, !llfi_index !22
  %11 = load i32* %i, align 4, !llfi_index !23
  call void @doProfiling(i32 27)
  %12 = add nsw i32 %11, 1, !llfi_index !24
  call void @doProfiling(i32 8)
  store i32 %12, i32* %i, align 4, !llfi_index !25
  br label %bb1, !llfi_index !26

bb1:                                              ; preds = %bb, %entry
  %13 = load i32* %i, align 4, !llfi_index !27
  call void @doProfiling(i32 27)
  %14 = icmp sle i32 %13, 4, !llfi_index !28
  call void @doProfiling(i32 42)
  br i1 %14, label %bb, label %bb2, !llfi_index !29

bb2:                                              ; preds = %bb1
  %15 = getelementptr inbounds [5 x i32]* %arr, i64 0, i64 0, !llfi_index !30
  call void @doProfiling(i32 29)
  %16 = load i32* %15, align 4, !llfi_index !31
  call void @doProfiling(i32 27)
  store i32 %16, i32* %min, align 4, !llfi_index !32
  store i32 1, i32* %i, align 4, !llfi_index !33
  br label %bb6, !llfi_index !34

bb3:                                              ; preds = %bb6
  %17 = load i32* %i, align 4, !llfi_index !35
  call void @doProfiling(i32 27)
  %18 = sext i32 %17 to i64, !llfi_index !36
  call void @doProfiling(i32 32)
  %19 = getelementptr inbounds [5 x i32]* %arr, i64 0, i64 %18, !llfi_index !37
  call void @doProfiling(i32 29)
  %20 = load i32* %19, align 4, !llfi_index !38
  call void @doProfiling(i32 27)
  %21 = load i32* %min, align 4, !llfi_index !39
  call void @doProfiling(i32 27)
  %22 = icmp slt i32 %20, %21, !llfi_index !40
  call void @doProfiling(i32 42)
  br i1 %22, label %bb4, label %bb5, !llfi_index !41

bb4:                                              ; preds = %bb3
  %23 = load i32* %i, align 4, !llfi_index !42
  call void @doProfiling(i32 27)
  %24 = sext i32 %23 to i64, !llfi_index !43
  call void @doProfiling(i32 32)
  %25 = getelementptr inbounds [5 x i32]* %arr, i64 0, i64 %24, !llfi_index !44
  call void @doProfiling(i32 29)
  %26 = load i32* %25, align 4, !llfi_index !45
  call void @doProfiling(i32 27)
  store i32 %26, i32* %min, align 4, !llfi_index !46
  br label %bb5, !llfi_index !47

bb5:                                              ; preds = %bb4, %bb3
  %27 = load i32* %i, align 4, !llfi_index !48
  call void @doProfiling(i32 27)
  %28 = add nsw i32 %27, 1, !llfi_index !49
  call void @doProfiling(i32 8)
  store i32 %28, i32* %i, align 4, !llfi_index !50
  br label %bb6, !llfi_index !51

bb6:                                              ; preds = %bb5, %bb2
  %29 = load i32* %i, align 4, !llfi_index !52
  call void @doProfiling(i32 27)
  %30 = icmp sle i32 %29, 4, !llfi_index !53
  call void @doProfiling(i32 42)
  br i1 %30, label %bb3, label %bb7, !llfi_index !54

bb7:                                              ; preds = %bb6
  %31 = load i32* %min, align 4, !llfi_index !55
  call void @doProfiling(i32 27)
  %32 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([10 x i8]* @.str, i64 0, i64 0), i32 %31) nounwind, !llfi_index !56
  call void @doProfiling(i32 45)
  store i32 0, i32* %0, align 4, !llfi_index !57
  %33 = load i32* %0, align 4, !llfi_index !58
  call void @doProfiling(i32 27)
  store i32 %33, i32* %retval, align 4, !llfi_index !59
  br label %return, !llfi_index !60

return:                                           ; preds = %bb7
  %retval8 = load i32* %retval, !llfi_index !61
  call void @doProfiling(i32 27)
  call void @endProfiling()
  ret i32 %retval8, !llfi_index !62
}

declare i32 @atoi(...)

declare i32 @printf(i8* noalias, ...) nounwind

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
