; ModuleID = '/ubc/ece/home/kp/grads/raiyat/Desktop/12thjune/LLFI-Cisco/test_programs/BufferUnderflow(API)/memcpy1.c'
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
  %retval = alloca i32
  %0 = alloca i32
  %size = alloca i32
  %src = alloca i8*
  %dest = alloca i8*
  %fp = alloca %struct.FILE*
  %i = alloca i32
  %ch = alloca i8
  %"alloca point" = bitcast i32 0 to i32
  store i32 50, i32* %size, align 4
  %1 = load i32* %size, align 4
  %2 = sext i32 %1 to i64
  %3 = call noalias i8* @malloc(i64 %2) nounwind
  store i8* %3, i8** %src, align 8
  %4 = load i8** %src, align 8
  %5 = icmp eq i8* %4, null
  br i1 %5, label %bb, label %bb1

bb:                                               ; preds = %entry
  %6 = call i32 @puts(i8* getelementptr inbounds ([56 x i8]* @.str, i64 0, i64 0)) nounwind
  store i32 0, i32* %0, align 4
  br label %bb11

bb1:                                              ; preds = %entry
  %7 = load i32* %size, align 4
  %8 = sext i32 %7 to i64
  %9 = call noalias i8* @malloc(i64 %8) nounwind
  store i8* %9, i8** %dest, align 8
  %10 = load i8** %dest, align 8
  %11 = icmp eq i8* %10, getelementptr inbounds ([5 x i8]* @.str1, i64 0, i64 0)
  br i1 %11, label %bb2, label %bb3

bb2:                                              ; preds = %bb1
  %12 = call i32 @puts(i8* getelementptr inbounds ([57 x i8]* @.str2, i64 0, i64 0)) nounwind
  store i32 0, i32* %0, align 4
  br label %bb11

bb3:                                              ; preds = %bb1
  %13 = call %struct.FILE* @fopen(i8* noalias getelementptr inbounds ([11 x i8]* @.str3, i64 0, i64 0), i8* noalias getelementptr inbounds ([2 x i8]* @.str4, i64 0, i64 0)) nounwind
  store %struct.FILE* %13, %struct.FILE** %fp, align 8
  %14 = load %struct.FILE** %fp, align 8
  %15 = icmp eq %struct.FILE* %14, null
  br i1 %15, label %bb4, label %bb5

bb4:                                              ; preds = %bb3
  %16 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([7 x i8]* @.str5, i64 0, i64 0)) nounwind
  br label %bb5

bb5:                                              ; preds = %bb4, %bb3
  %17 = load i32* %size, align 4
  %18 = sext i32 %17 to i64
  %19 = load i8** %src, align 8
  %20 = load %struct.FILE** %fp, align 8
  %21 = call i64 @fread(i8* noalias %19, i64 1, i64 %18, %struct.FILE* noalias %20) nounwind
  %22 = load %struct.FILE** %fp, align 8
  %23 = call i32 @fclose(%struct.FILE* %22) nounwind
  %24 = load i8** %src, align 8
  %25 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([35 x i8]* @.str6, i64 0, i64 0), i8* %24) nounwind
  %26 = load i8** %dest, align 8
  %27 = load i8** %src, align 8
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %26, i8* %27, i64 50, i32 1, i1 false)
  %28 = load i8** %dest, align 8
  %29 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([30 x i8]* @.str7, i64 0, i64 0), i8* %28) nounwind
  %30 = call %struct.FILE* @fopen(i8* noalias getelementptr inbounds ([11 x i8]* @.str8, i64 0, i64 0), i8* noalias getelementptr inbounds ([2 x i8]* @.str9, i64 0, i64 0)) nounwind
  store %struct.FILE* %30, %struct.FILE** %fp, align 8
  %31 = load %struct.FILE** %fp, align 8
  %32 = icmp ne %struct.FILE* %31, null
  br i1 %32, label %bb6, label %bb7

bb6:                                              ; preds = %bb5
  %33 = load i32* %size, align 4
  %34 = sext i32 %33 to i64
  %35 = load i8** %dest, align 8
  %36 = load %struct.FILE** %fp, align 8
  %37 = call i64 @fwrite(i8* noalias %35, i64 1, i64 %34, %struct.FILE* noalias %36) nounwind
  br label %bb7

bb7:                                              ; preds = %bb6, %bb5
  %38 = load %struct.FILE** %fp, align 8
  %39 = call i32 @fclose(%struct.FILE* %38) nounwind
  %40 = call %struct.FILE* @fopen(i8* noalias getelementptr inbounds ([11 x i8]* @.str8, i64 0, i64 0), i8* noalias getelementptr inbounds ([2 x i8]* @.str4, i64 0, i64 0)) nounwind
  %41 = call i32 @puts(i8* getelementptr inbounds ([33 x i8]* @.str10, i64 0, i64 0)) nounwind
  %42 = load %struct.FILE** %fp, align 8
  %43 = call i32 @fgetc(%struct.FILE* %42) nounwind
  %44 = trunc i32 %43 to i8
  store i8 %44, i8* %ch, align 1
  br label %bb9

bb8:                                              ; preds = %bb9
  %45 = load i8* %ch, align 1
  %46 = sext i8 %45 to i32
  %47 = call i32 @putchar(i32 %46) nounwind
  %48 = load %struct.FILE** %fp, align 8
  %49 = call i32 @fgetc(%struct.FILE* %48) nounwind
  %50 = trunc i32 %49 to i8
  store i8 %50, i8* %ch, align 1
  br label %bb9

bb9:                                              ; preds = %bb8, %bb7
  %51 = load i8* %ch, align 1
  %52 = icmp ne i8 %51, -1
  br i1 %52, label %bb8, label %bb10

bb10:                                             ; preds = %bb9
  %53 = load %struct.FILE** %fp, align 8
  %54 = call i32 @fclose(%struct.FILE* %53) nounwind
  %55 = load i8** %src, align 8
  call void @free(i8* %55) nounwind
  %56 = load i8** %dest, align 8
  call void @free(i8* %56) nounwind
  store i32 0, i32* %0, align 4
  br label %bb11

bb11:                                             ; preds = %bb10, %bb2, %bb
  %57 = load i32* %0, align 4
  store i32 %57, i32* %retval, align 4
  br label %return

return:                                           ; preds = %bb11
  %retval12 = load i32* %retval
  ret i32 %retval12
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
