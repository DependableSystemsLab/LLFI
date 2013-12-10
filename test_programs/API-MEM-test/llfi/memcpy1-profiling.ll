; ModuleID = '/ubc/ece/home/kp/grads/raiyat/newproject/LLFI-Cisco-master/test_programs/Mem-F1/llfi/memcpy1-llfi_index.ll'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-f128:128:128-n8:16:32:64"
target triple = "x86_64-unknown-linux-gnu"

%struct.FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct.FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct.FILE*, i32 }

@.str = private unnamed_addr constant [11 x i8] c"sample.txt\00", align 1
@.str1 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@.str2 = private unnamed_addr constant [7 x i8] c"ERROR!\00", align 1
@.str3 = private unnamed_addr constant [35 x i8] c"The content of input file is:  %s\0A\00", align 8
@.str4 = private unnamed_addr constant [30 x i8] c"The content of buffer is: %s\0A\00", align 1
@.str5 = private unnamed_addr constant [11 x i8] c"output.txt\00", align 1
@.str6 = private unnamed_addr constant [2 x i8] c"w\00", align 1
@.str7 = private unnamed_addr constant [27 x i8] c" the content of file are :\00", align 1

define i32 @main() nounwind {
entry:
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
  %4 = load i32* %size, align 4, !llfi_index !14
  %5 = sext i32 %4 to i64, !llfi_index !15
  %6 = call noalias i8* @malloc(i64 %5) nounwind, !llfi_index !16
  store i8* %6, i8** %dest, align 8, !llfi_index !17
  %7 = call %struct.FILE* @fopen(i8* noalias getelementptr inbounds ([11 x i8]* @.str, i64 0, i64 0), i8* noalias getelementptr inbounds ([2 x i8]* @.str1, i64 0, i64 0)) nounwind, !llfi_index !18
  store %struct.FILE* %7, %struct.FILE** %fp, align 8, !llfi_index !19
  %8 = load %struct.FILE** %fp, align 8, !llfi_index !20
  %9 = icmp eq %struct.FILE* %8, null, !llfi_index !21
  br i1 %9, label %bb, label %bb1, !llfi_index !22

bb:                                               ; preds = %entry
  %10 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([7 x i8]* @.str2, i64 0, i64 0)) nounwind, !llfi_index !23
  br label %bb1, !llfi_index !24

bb1:                                              ; preds = %bb, %entry
  %11 = load i32* %size, align 4, !llfi_index !25
  %12 = sext i32 %11 to i64, !llfi_index !26
  %13 = load i8** %src, align 8, !llfi_index !27
  %14 = load %struct.FILE** %fp, align 8, !llfi_index !28
  %15 = call i64 @fread(i8* noalias %13, i64 1, i64 %12, %struct.FILE* noalias %14) nounwind, !llfi_index !29
  %16 = load %struct.FILE** %fp, align 8, !llfi_index !30
  %17 = call i32 @fclose(%struct.FILE* %16) nounwind, !llfi_index !31
  %18 = load i8** %src, align 8, !llfi_index !32
  %19 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([35 x i8]* @.str3, i64 0, i64 0), i8* %18) nounwind, !llfi_index !33
  %20 = load i8** %dest, align 8, !llfi_index !34
  %21 = load i8** %src, align 8, !llfi_index !35
  call void @doProfiling(i32 45)
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %20, i8* %21, i64 50, i32 1, i1 false), !llfi_index !36
  %22 = load i8** %dest, align 8, !llfi_index !37
  %23 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([30 x i8]* @.str4, i64 0, i64 0), i8* %22) nounwind, !llfi_index !38
  %24 = call %struct.FILE* @fopen(i8* noalias getelementptr inbounds ([11 x i8]* @.str5, i64 0, i64 0), i8* noalias getelementptr inbounds ([2 x i8]* @.str6, i64 0, i64 0)) nounwind, !llfi_index !39
  store %struct.FILE* %24, %struct.FILE** %fp, align 8, !llfi_index !40
  %25 = load %struct.FILE** %fp, align 8, !llfi_index !41
  %26 = icmp ne %struct.FILE* %25, null, !llfi_index !42
  br i1 %26, label %bb2, label %bb3, !llfi_index !43

bb2:                                              ; preds = %bb1
  %27 = load i32* %size, align 4, !llfi_index !44
  %28 = sext i32 %27 to i64, !llfi_index !45
  %29 = load i8** %dest, align 8, !llfi_index !46
  %30 = load %struct.FILE** %fp, align 8, !llfi_index !47
  %31 = call i64 @fwrite(i8* noalias %29, i64 1, i64 %28, %struct.FILE* noalias %30) nounwind, !llfi_index !48
  br label %bb3, !llfi_index !49

bb3:                                              ; preds = %bb2, %bb1
  %32 = load %struct.FILE** %fp, align 8, !llfi_index !50
  %33 = call i32 @fclose(%struct.FILE* %32) nounwind, !llfi_index !51
  %34 = call %struct.FILE* @fopen(i8* noalias getelementptr inbounds ([11 x i8]* @.str5, i64 0, i64 0), i8* noalias getelementptr inbounds ([2 x i8]* @.str1, i64 0, i64 0)) nounwind, !llfi_index !52
  %35 = call i32 @puts(i8* getelementptr inbounds ([27 x i8]* @.str7, i64 0, i64 0)) nounwind, !llfi_index !53
  %36 = load %struct.FILE** %fp, align 8, !llfi_index !54
  %37 = call i32 @fgetc(%struct.FILE* %36) nounwind, !llfi_index !55
  %38 = trunc i32 %37 to i8, !llfi_index !56
  store i8 %38, i8* %ch, align 1, !llfi_index !57
  br label %bb5, !llfi_index !58

bb4:                                              ; preds = %bb5
  %39 = load i8* %ch, align 1, !llfi_index !59
  %40 = sext i8 %39 to i32, !llfi_index !60
  %41 = call i32 @putchar(i32 %40) nounwind, !llfi_index !61
  %42 = load %struct.FILE** %fp, align 8, !llfi_index !62
  %43 = call i32 @fgetc(%struct.FILE* %42) nounwind, !llfi_index !63
  %44 = trunc i32 %43 to i8, !llfi_index !64
  store i8 %44, i8* %ch, align 1, !llfi_index !65
  br label %bb5, !llfi_index !66

bb5:                                              ; preds = %bb4, %bb3
  %45 = load i8* %ch, align 1, !llfi_index !67
  %46 = icmp ne i8 %45, -1, !llfi_index !68
  br i1 %46, label %bb4, label %bb6, !llfi_index !69

bb6:                                              ; preds = %bb5
  %47 = load %struct.FILE** %fp, align 8, !llfi_index !70
  %48 = call i32 @fclose(%struct.FILE* %47) nounwind, !llfi_index !71
  %49 = load i8** %src, align 8, !llfi_index !72
  call void @free(i8* %49) nounwind, !llfi_index !73
  %50 = load i8** %dest, align 8, !llfi_index !74
  call void @free(i8* %50) nounwind, !llfi_index !75
  store i32 0, i32* %0, align 4, !llfi_index !76
  %51 = load i32* %0, align 4, !llfi_index !77
  store i32 %51, i32* %retval, align 4, !llfi_index !78
  br label %return, !llfi_index !79

return:                                           ; preds = %bb6
  %retval7 = load i32* %retval, !llfi_index !80
  call void @endProfiling()
  ret i32 %retval7, !llfi_index !81
}

declare noalias i8* @malloc(i64) nounwind

declare %struct.FILE* @fopen(i8* noalias, i8* noalias)

declare i32 @printf(i8* noalias, ...) nounwind

declare i64 @fread(i8* noalias, i64, i64, %struct.FILE* noalias)

declare i32 @fclose(%struct.FILE*)

declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture, i64, i32, i1) nounwind

declare i64 @fwrite(i8* noalias, i64, i64, %struct.FILE* noalias)

declare i32 @puts(i8*)

declare i32 @fgetc(%struct.FILE*)

declare i32 @putchar(i32)

declare void @free(i8*) nounwind

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
