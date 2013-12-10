; ModuleID = '/ubc/ece/home/kp/grads/raiyat/newproject/LLFI-Cisco-master/test_programs/Mem-F1/memcpy1.c'
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
  %4 = load i32* %size, align 4
  %5 = sext i32 %4 to i64
  %6 = call noalias i8* @malloc(i64 %5) nounwind
  store i8* %6, i8** %dest, align 8
  %7 = call %struct.FILE* @fopen(i8* noalias getelementptr inbounds ([11 x i8]* @.str, i64 0, i64 0), i8* noalias getelementptr inbounds ([2 x i8]* @.str1, i64 0, i64 0)) nounwind
  store %struct.FILE* %7, %struct.FILE** %fp, align 8
  %8 = load %struct.FILE** %fp, align 8
  %9 = icmp eq %struct.FILE* %8, null
  br i1 %9, label %bb, label %bb1

bb:                                               ; preds = %entry
  %10 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([7 x i8]* @.str2, i64 0, i64 0)) nounwind
  br label %bb1

bb1:                                              ; preds = %bb, %entry
  %11 = load i32* %size, align 4
  %12 = sext i32 %11 to i64
  %13 = load i8** %src, align 8
  %14 = load %struct.FILE** %fp, align 8
  %15 = call i64 @fread(i8* noalias %13, i64 1, i64 %12, %struct.FILE* noalias %14) nounwind
  %16 = load %struct.FILE** %fp, align 8
  %17 = call i32 @fclose(%struct.FILE* %16) nounwind
  %18 = load i8** %src, align 8
  %19 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([35 x i8]* @.str3, i64 0, i64 0), i8* %18) nounwind
  %20 = load i8** %dest, align 8
  %21 = load i8** %src, align 8
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %20, i8* %21, i64 50, i32 1, i1 false)
  %22 = load i8** %dest, align 8
  %23 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([30 x i8]* @.str4, i64 0, i64 0), i8* %22) nounwind
  %24 = call %struct.FILE* @fopen(i8* noalias getelementptr inbounds ([11 x i8]* @.str5, i64 0, i64 0), i8* noalias getelementptr inbounds ([2 x i8]* @.str6, i64 0, i64 0)) nounwind
  store %struct.FILE* %24, %struct.FILE** %fp, align 8
  %25 = load %struct.FILE** %fp, align 8
  %26 = icmp ne %struct.FILE* %25, null
  br i1 %26, label %bb2, label %bb3

bb2:                                              ; preds = %bb1
  %27 = load i32* %size, align 4
  %28 = sext i32 %27 to i64
  %29 = load i8** %dest, align 8
  %30 = load %struct.FILE** %fp, align 8
  %31 = call i64 @fwrite(i8* noalias %29, i64 1, i64 %28, %struct.FILE* noalias %30) nounwind
  br label %bb3

bb3:                                              ; preds = %bb2, %bb1
  %32 = load %struct.FILE** %fp, align 8
  %33 = call i32 @fclose(%struct.FILE* %32) nounwind
  %34 = call %struct.FILE* @fopen(i8* noalias getelementptr inbounds ([11 x i8]* @.str5, i64 0, i64 0), i8* noalias getelementptr inbounds ([2 x i8]* @.str1, i64 0, i64 0)) nounwind
  %35 = call i32 @puts(i8* getelementptr inbounds ([27 x i8]* @.str7, i64 0, i64 0)) nounwind
  %36 = load %struct.FILE** %fp, align 8
  %37 = call i32 @fgetc(%struct.FILE* %36) nounwind
  %38 = trunc i32 %37 to i8
  store i8 %38, i8* %ch, align 1
  br label %bb5

bb4:                                              ; preds = %bb5
  %39 = load i8* %ch, align 1
  %40 = sext i8 %39 to i32
  %41 = call i32 @putchar(i32 %40) nounwind
  %42 = load %struct.FILE** %fp, align 8
  %43 = call i32 @fgetc(%struct.FILE* %42) nounwind
  %44 = trunc i32 %43 to i8
  store i8 %44, i8* %ch, align 1
  br label %bb5

bb5:                                              ; preds = %bb4, %bb3
  %45 = load i8* %ch, align 1
  %46 = icmp ne i8 %45, -1
  br i1 %46, label %bb4, label %bb6

bb6:                                              ; preds = %bb5
  %47 = load %struct.FILE** %fp, align 8
  %48 = call i32 @fclose(%struct.FILE* %47) nounwind
  %49 = load i8** %src, align 8
  call void @free(i8* %49) nounwind
  %50 = load i8** %dest, align 8
  call void @free(i8* %50) nounwind
  store i32 0, i32* %0, align 4
  %51 = load i32* %0, align 4
  store i32 %51, i32* %retval, align 4
  br label %return

return:                                           ; preds = %bb6
  %retval7 = load i32* %retval
  ret i32 %retval7
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
