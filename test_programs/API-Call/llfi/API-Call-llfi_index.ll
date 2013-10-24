; ModuleID = '/ubc/ece/home/am/grads/raiyat/project/LLFI/test_programs/API-Call/API-Call.ll'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-f128:128:128-n8:16:32:64"
target triple = "x86_64-unknown-linux-gnu"

%struct.FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct.FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct.FILE*, i32 }

@.str = private unnamed_addr constant [11 x i8] c"sample.txt\00", align 1
@.str1 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@.str2 = private unnamed_addr constant [31 x i8] c"Error while opening the file.\0A\00", align 8
@.str3 = private unnamed_addr constant [27 x i8] c" the content of file are :\00", align 1

define i32 @main() nounwind {
entry:
  %retval = alloca i32, !llfi_index !0
  %0 = alloca i32, !llfi_index !1
  %ch = alloca i8, !llfi_index !2
  %file_name = alloca [25 x i8], !llfi_index !3
  %fp = alloca %struct.FILE*, !llfi_index !4
  %"alloca point" = bitcast i32 0 to i32, !llfi_index !5
  %1 = call %struct.FILE* @fopen(i8* noalias getelementptr inbounds ([11 x i8]* @.str, i64 0, i64 0), i8* noalias getelementptr inbounds ([2 x i8]* @.str1, i64 0, i64 0)) nounwind, !llfi_index !6
  store %struct.FILE* %1, %struct.FILE** %fp, align 8, !llfi_index !7
  %2 = load %struct.FILE** %fp, align 8, !llfi_index !8
  %3 = icmp eq %struct.FILE* %2, null, !llfi_index !9
  br i1 %3, label %bb, label %bb1, !llfi_index !10

bb:                                               ; preds = %entry
  call void @perror(i8* getelementptr inbounds ([31 x i8]* @.str2, i64 0, i64 0)) nounwind, !llfi_index !11
  call void @exit(i32 1) noreturn nounwind, !llfi_index !12
  unreachable, !llfi_index !13

bb1:                                              ; preds = %entry
  %4 = call i32 @puts(i8* getelementptr inbounds ([27 x i8]* @.str3, i64 0, i64 0)) nounwind, !llfi_index !14
  br label %bb2, !llfi_index !15

bb2:                                              ; preds = %bb2, %bb1
  %5 = load %struct.FILE** %fp, align 8, !llfi_index !16
  %6 = call i32 @fgetc(%struct.FILE* %5) nounwind, !llfi_index !17
  %7 = trunc i32 %6 to i8, !llfi_index !18
  store i8 %7, i8* %ch, align 1, !llfi_index !19
  %8 = load i8* %ch, align 1, !llfi_index !20
  %9 = sext i8 %8 to i32, !llfi_index !21
  %10 = call i32 @putchar(i32 %9) nounwind, !llfi_index !22
  %11 = load i8* %ch, align 1, !llfi_index !23
  %12 = icmp ne i8 %11, -1, !llfi_index !24
  br i1 %12, label %bb2, label %bb3, !llfi_index !25

bb3:                                              ; preds = %bb2
  %13 = load %struct.FILE** %fp, align 8, !llfi_index !26
  %14 = call i32 @fclose(%struct.FILE* %13) nounwind, !llfi_index !27
  store i32 0, i32* %0, align 4, !llfi_index !28
  %15 = load i32* %0, align 4, !llfi_index !29
  store i32 %15, i32* %retval, align 4, !llfi_index !30
  br label %return, !llfi_index !31

return:                                           ; preds = %bb3
  %retval4 = load i32* %retval, !llfi_index !32
  ret i32 %retval4, !llfi_index !33
}

declare %struct.FILE* @fopen(i8* noalias, i8* noalias)

declare void @perror(i8*)

declare void @exit(i32) noreturn nounwind

declare i32 @puts(i8*)

declare i32 @fgetc(%struct.FILE*)

declare i32 @putchar(i32)

declare i32 @fclose(%struct.FILE*)

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
