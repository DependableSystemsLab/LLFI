; ModuleID = '/ubc/ece/home/kp/grads/raiyat/newproject/LLFI-Cisco-master/LLFI-GUI/memcpy1/llfi/memcpy1-llfi_index.ll'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-f128:128:128-n8:16:32:64"
target triple = "x86_64-unknown-linux-gnu"

%struct.FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct.FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct.FILE*, i32 }

@.str = private unnamed_addr constant [56 x i8] c" src can't be created;The system is ran out of memory :\00", align 8
@.str1 = private unnamed_addr constant [5 x i8] c"NULL\00", align 1
@.str2 = private unnamed_addr constant [57 x i8] c" dest can't be created;The system is ran out of memory :\00", align 8
@.str3 = private unnamed_addr constant [11 x i8] c"sample.txt\00", align 1
@.str4 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@.str5 = private unnamed_addr constant [7 x i8] c"ERROR!\00", align 1
@.str6 = private unnamed_addr constant [35 x i8] c"The content of input file is:  %s\0A\00", align 8
@.str7 = private unnamed_addr constant [30 x i8] c"The content of buffer is: %s\0A\00", align 1
@.str8 = private unnamed_addr constant [11 x i8] c"output.txt\00", align 1
@.str9 = private unnamed_addr constant [2 x i8] c"w\00", align 1
@.str10 = private unnamed_addr constant [33 x i8] c" the content of OUTPUT file is :\00", align 8

define i32 @main() nounwind {
entry:
  call void @initInjections()
  %retval = alloca i32, !llfi_index !0
  %0 = alloca i32, !llfi_index !1
  %size = alloca i32, !llfi_index !2
  %src = alloca i8*, !llfi_index !3
  %dest = alloca i8*, !llfi_index !4
  %fp = alloca %struct.FILE*, !llfi_index !5
  %i = alloca i32, !llfi_index !6
  %ch = alloca i8, !llfi_index !7
  %"alloca point" = bitcast i32 0 to i32, !llfi_index !8
  store i32 50, i32* %size, align 4, !llfi_index !9
  %1 = load i32* %size, align 4, !llfi_index !10
  %2 = sext i32 %1 to i64, !llfi_index !11
  %3 = call noalias i8* @malloc(i64 %2) nounwind, !llfi_index !12
  store i8* %3, i8** %src, align 8, !llfi_index !13
  %4 = load i8** %src, align 8, !llfi_index !14
  %5 = icmp eq i8* %4, null, !llfi_index !15
  br i1 %5, label %bb, label %bb1, !llfi_index !16

bb:                                               ; preds = %entry
  %6 = call i32 @puts(i8* getelementptr inbounds ([56 x i8]* @.str, i64 0, i64 0)) nounwind, !llfi_index !17
  store i32 0, i32* %0, align 4, !llfi_index !18
  br label %bb11, !llfi_index !19

bb1:                                              ; preds = %entry
  %7 = load i32* %size, align 4, !llfi_index !20
  %8 = sext i32 %7 to i64, !llfi_index !21
  %9 = call noalias i8* @malloc(i64 %8) nounwind, !llfi_index !22
  store i8* %9, i8** %dest, align 8, !llfi_index !23
  %10 = load i8** %dest, align 8, !llfi_index !24
  %11 = icmp eq i8* %10, getelementptr inbounds ([5 x i8]* @.str1, i64 0, i64 0), !llfi_index !25
  br i1 %11, label %bb2, label %bb3, !llfi_index !26

bb2:                                              ; preds = %bb1
  %12 = call i32 @puts(i8* getelementptr inbounds ([57 x i8]* @.str2, i64 0, i64 0)) nounwind, !llfi_index !27
  store i32 0, i32* %0, align 4, !llfi_index !28
  br label %bb11, !llfi_index !29

bb3:                                              ; preds = %bb1
  %13 = call %struct.FILE* @fopen(i8* noalias getelementptr inbounds ([11 x i8]* @.str3, i64 0, i64 0), i8* noalias getelementptr inbounds ([2 x i8]* @.str4, i64 0, i64 0)) nounwind, !llfi_index !30
  store %struct.FILE* %13, %struct.FILE** %fp, align 8, !llfi_index !31
  %14 = load %struct.FILE** %fp, align 8, !llfi_index !32
  %15 = icmp eq %struct.FILE* %14, null, !llfi_index !33
  br i1 %15, label %bb4, label %bb5, !llfi_index !34

bb4:                                              ; preds = %bb3
  %16 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([7 x i8]* @.str5, i64 0, i64 0)) nounwind, !llfi_index !35
  br label %bb5, !llfi_index !36

bb5:                                              ; preds = %bb4, %bb3
  %17 = load i32* %size, align 4, !llfi_index !37
  %18 = sext i32 %17 to i64, !llfi_index !38
  %19 = load i8** %src, align 8, !llfi_index !39
  %20 = load %struct.FILE** %fp, align 8, !llfi_index !40
  %fi = call i64 @injectFault0(i64 41, i64 1, i32 45, i32 0, i32 1)
  %21 = call i64 @fread(i8* noalias %19, i64 %fi, i64 %18, %struct.FILE* noalias %20) nounwind, !llfi_index !41
  %22 = load %struct.FILE** %fp, align 8, !llfi_index !42
  %23 = call i32 @fclose(%struct.FILE* %22) nounwind, !llfi_index !43
  %24 = load i8** %src, align 8, !llfi_index !44
  %25 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([35 x i8]* @.str6, i64 0, i64 0), i8* %24) nounwind, !llfi_index !45
  %26 = load i8** %dest, align 8, !llfi_index !46
  %27 = load i8** %src, align 8, !llfi_index !47
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %26, i8* %27, i64 50, i32 1, i1 false), !llfi_index !48
  %28 = load i8** %dest, align 8, !llfi_index !49
  %29 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([30 x i8]* @.str7, i64 0, i64 0), i8* %28) nounwind, !llfi_index !50
  %30 = call %struct.FILE* @fopen(i8* noalias getelementptr inbounds ([11 x i8]* @.str8, i64 0, i64 0), i8* noalias getelementptr inbounds ([2 x i8]* @.str9, i64 0, i64 0)) nounwind, !llfi_index !51
  store %struct.FILE* %30, %struct.FILE** %fp, align 8, !llfi_index !52
  %31 = load %struct.FILE** %fp, align 8, !llfi_index !53
  %32 = icmp ne %struct.FILE* %31, null, !llfi_index !54
  br i1 %32, label %bb6, label %bb7, !llfi_index !55

bb6:                                              ; preds = %bb5
  %33 = load i32* %size, align 4, !llfi_index !56
  %34 = sext i32 %33 to i64, !llfi_index !57
  %35 = load i8** %dest, align 8, !llfi_index !58
  %36 = load %struct.FILE** %fp, align 8, !llfi_index !59
  %37 = call i64 @fwrite(i8* noalias %35, i64 1, i64 %34, %struct.FILE* noalias %36) nounwind, !llfi_index !60
  br label %bb7, !llfi_index !61

bb7:                                              ; preds = %bb6, %bb5
  %38 = load %struct.FILE** %fp, align 8, !llfi_index !62
  %39 = call i32 @fclose(%struct.FILE* %38) nounwind, !llfi_index !63
  %40 = call %struct.FILE* @fopen(i8* noalias getelementptr inbounds ([11 x i8]* @.str8, i64 0, i64 0), i8* noalias getelementptr inbounds ([2 x i8]* @.str4, i64 0, i64 0)) nounwind, !llfi_index !64
  %41 = call i32 @puts(i8* getelementptr inbounds ([33 x i8]* @.str10, i64 0, i64 0)) nounwind, !llfi_index !65
  %42 = load %struct.FILE** %fp, align 8, !llfi_index !66
  %43 = call i32 @fgetc(%struct.FILE* %42) nounwind, !llfi_index !67
  %44 = trunc i32 %43 to i8, !llfi_index !68
  store i8 %44, i8* %ch, align 1, !llfi_index !69
  br label %bb9, !llfi_index !70

bb8:                                              ; preds = %bb9
  %45 = load i8* %ch, align 1, !llfi_index !71
  %46 = sext i8 %45 to i32, !llfi_index !72
  %47 = call i32 @putchar(i32 %46) nounwind, !llfi_index !73
  %48 = load %struct.FILE** %fp, align 8, !llfi_index !74
  %49 = call i32 @fgetc(%struct.FILE* %48) nounwind, !llfi_index !75
  %50 = trunc i32 %49 to i8, !llfi_index !76
  store i8 %50, i8* %ch, align 1, !llfi_index !77
  br label %bb9, !llfi_index !78

bb9:                                              ; preds = %bb8, %bb7
  %51 = load i8* %ch, align 1, !llfi_index !79
  %52 = icmp ne i8 %51, -1, !llfi_index !80
  br i1 %52, label %bb8, label %bb10, !llfi_index !81

bb10:                                             ; preds = %bb9
  %53 = load %struct.FILE** %fp, align 8, !llfi_index !82
  %54 = call i32 @fclose(%struct.FILE* %53) nounwind, !llfi_index !83
  %55 = load i8** %src, align 8, !llfi_index !84
  call void @free(i8* %55) nounwind, !llfi_index !85
  %56 = load i8** %dest, align 8, !llfi_index !86
  call void @free(i8* %56) nounwind, !llfi_index !87
  store i32 0, i32* %0, align 4, !llfi_index !88
  br label %bb11, !llfi_index !89

bb11:                                             ; preds = %bb10, %bb2, %bb
  %57 = load i32* %0, align 4, !llfi_index !90
  store i32 %57, i32* %retval, align 4, !llfi_index !91
  br label %return, !llfi_index !92

return:                                           ; preds = %bb11
  %retval12 = load i32* %retval, !llfi_index !93
  call void @postInjections()
  ret i32 %retval12, !llfi_index !94
}

declare noalias i8* @malloc(i64) nounwind

declare i32 @puts(i8*)

declare %struct.FILE* @fopen(i8* noalias, i8* noalias)

declare i32 @printf(i8* noalias, ...) nounwind

declare i64 @fread(i8* noalias, i64, i64, %struct.FILE* noalias)

declare i32 @fclose(%struct.FILE*)

declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture, i64, i32, i1) nounwind

declare i64 @fwrite(i8* noalias, i64, i64, %struct.FILE* noalias)

declare i32 @fgetc(%struct.FILE*)

declare i32 @putchar(i32)

declare void @free(i8*) nounwind

define i64 @injectFault0(i64, i64, i32, i32, i32) {
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
!63 = metadata !{i64 63}
!64 = metadata !{i64 64}
!65 = metadata !{i64 65}
!66 = metadata !{i64 66}
!67 = metadata !{i64 67}
!68 = metadata !{i64 68}
!69 = metadata !{i64 69}
!70 = metadata !{i64 70}
!71 = metadata !{i64 71}
!72 = metadata !{i64 72}
!73 = metadata !{i64 73}
!74 = metadata !{i64 74}
!75 = metadata !{i64 75}
!76 = metadata !{i64 76}
!77 = metadata !{i64 77}
!78 = metadata !{i64 78}
!79 = metadata !{i64 79}
!80 = metadata !{i64 80}
!81 = metadata !{i64 81}
!82 = metadata !{i64 82}
!83 = metadata !{i64 83}
!84 = metadata !{i64 84}
!85 = metadata !{i64 85}
!86 = metadata !{i64 86}
!87 = metadata !{i64 87}
!88 = metadata !{i64 88}
!89 = metadata !{i64 89}
!90 = metadata !{i64 90}
!91 = metadata !{i64 91}
!92 = metadata !{i64 92}
!93 = metadata !{i64 93}
!94 = metadata !{i64 94}
