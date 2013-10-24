; ModuleID = '/ubc/ece/home/am/grads/raiyat/project/LLFI/test_programs/API-Call/API-Call.c'
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
  %retval = alloca i32
  %0 = alloca i32
  %ch = alloca i8
  %file_name = alloca [25 x i8]
  %fp = alloca %struct.FILE*
  %"alloca point" = bitcast i32 0 to i32
  %1 = call %struct.FILE* @fopen(i8* noalias getelementptr inbounds ([11 x i8]* @.str, i64 0, i64 0), i8* noalias getelementptr inbounds ([2 x i8]* @.str1, i64 0, i64 0)) nounwind
  store %struct.FILE* %1, %struct.FILE** %fp, align 8
  %2 = load %struct.FILE** %fp, align 8
  %3 = icmp eq %struct.FILE* %2, null
  br i1 %3, label %bb, label %bb1

bb:                                               ; preds = %entry
  call void @perror(i8* getelementptr inbounds ([31 x i8]* @.str2, i64 0, i64 0)) nounwind
  call void @exit(i32 1) noreturn nounwind
  unreachable

bb1:                                              ; preds = %entry
  %4 = call i32 @puts(i8* getelementptr inbounds ([27 x i8]* @.str3, i64 0, i64 0)) nounwind
  br label %bb2

bb2:                                              ; preds = %bb2, %bb1
  %5 = load %struct.FILE** %fp, align 8
  %6 = call i32 @fgetc(%struct.FILE* %5) nounwind
  %7 = trunc i32 %6 to i8
  store i8 %7, i8* %ch, align 1
  %8 = load i8* %ch, align 1
  %9 = sext i8 %8 to i32
  %10 = call i32 @putchar(i32 %9) nounwind
  %11 = load i8* %ch, align 1
  %12 = icmp ne i8 %11, -1
  br i1 %12, label %bb2, label %bb3

bb3:                                              ; preds = %bb2
  %13 = load %struct.FILE** %fp, align 8
  %14 = call i32 @fclose(%struct.FILE* %13) nounwind
  store i32 0, i32* %0, align 4
  %15 = load i32* %0, align 4
  store i32 %15, i32* %retval, align 4
  br label %return

return:                                           ; preds = %bb3
  %retval4 = load i32* %retval
  ret i32 %retval4
}

declare %struct.FILE* @fopen(i8* noalias, i8* noalias)

declare void @perror(i8*)

declare void @exit(i32) noreturn nounwind

declare i32 @puts(i8*)

declare i32 @fgetc(%struct.FILE*)

declare i32 @putchar(i32)

declare i32 @fclose(%struct.FILE*)
