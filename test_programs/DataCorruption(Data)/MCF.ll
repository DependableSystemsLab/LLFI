; ModuleID = 'MCF.linked.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-f128:128:128-n8:16:32:64"
target triple = "x86_64-unknown-linux-gnu"

%struct.BASKET = type { %struct.arc*, i64, i64 }
%struct.FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct.FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct.FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct.FILE*, i32 }
%struct.arc = type { i64, %struct.node*, %struct.node*, i32, %struct.arc*, %struct.arc*, i64, i64 }
%struct.arc_t = type { i64, %struct.node*, %struct.node*, i32, %struct.arc*, %struct.arc*, i64, i64 }
%struct.network_t = type { [200 x i8], [200 x i8], i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, double, i64, %struct.node*, %struct.node*, %struct.arc*, %struct.arc*, %struct.arc*, %struct.arc*, i64, i64, i64 }
%struct.node = type { i64, i32, %struct.node*, %struct.node*, %struct.node*, %struct.node*, %struct.arc*, %struct.arc*, %struct.arc*, %struct.arc*, i64, i64, i32, i32 }
%struct.node_t = type { i64, i32, %struct.node*, %struct.node*, %struct.node*, %struct.node*, %struct.arc*, %struct.arc*, %struct.arc*, %struct.arc*, i64, i64, i32, i32 }

@.str = private unnamed_addr constant [20 x i8] c"net->max_new_m >= 3\00", align 1
@.str1 = private unnamed_addr constant [11 x i8] c"implicit.c\00", align 1
@__PRETTY_FUNCTION__.4371 = internal unnamed_addr constant [12 x i8] c"resize_prob\00"
@.str2 = private unnamed_addr constant [31 x i8] c"network %s: not enough memory\0A\00", align 8
@stdout = external unnamed_addr global %struct.FILE*
@net = common global %struct.network_t zeroinitializer, align 32
@.str3 = private constant [34 x i8] c"active arcs                : %ld\0A\00", align 8
@.str14 = private constant [34 x i8] c"simplex iterations         : %ld\0A\00", align 8
@.str25 = private constant [36 x i8] c"objective value            : %0.0f\0A\00", align 8
@.str36 = private constant [34 x i8] c"erased arcs                : %ld\0A\00", align 8
@.str4 = private constant [34 x i8] c"new implicit arcs          : %ld\0A\00", align 8
@.str5 = private constant [28 x i8] c"not enough memory, exit(-1)\00", align 1
@.str6 = private constant [34 x i8] c"checksum                   : %ld\0A\00", align 8
@.str7 = private constant [31 x i8] c"\0AMCF SPEC CPU2006 version 1.10\00", align 8
@.str8 = private constant [51 x i8] c"Copyright (c) 1998-2000 Zuse Institut Berlin (ZIB)\00", align 8
@.str9 = private constant [45 x i8] c"Copyright (c) 2000-2002 Andreas Loebel & ZIB\00", align 8
@.str10 = private constant [39 x i8] c"Copyright (c) 2003-2005 Andreas Loebel\00", align 8
@.str11 = private constant [17 x i8] c"read error, exit\00", align 1
@.str12 = private constant [34 x i8] c"nodes                      : %ld\0A\00", align 8
@.str13 = private constant [5 x i8] c"done\00", align 1
@.str147 = private constant [8 x i8] c"mcf.out\00", align 1
@.str15 = private constant [25 x i8] c"PRIMAL NETWORK SIMPLEX: \00", align 1
@.str116 = private constant [49 x i8] c"artificial arc with nonzero flow, node %d (%ld)\0A\00", align 8
@.str217 = private constant [31 x i8] c"basis primal infeasible (%ld)\0A\00", align 8
@stderr = external global %struct.FILE*
@.str318 = private constant [23 x i8] c"DUAL NETWORK SIMPLEX: \00", align 1
@.str419 = private constant [23 x i8] c"basis dual infeasible\0A\00", align 1
@.str23 = private constant [2 x i8] c"w\00", align 1
@.str124 = private constant [4 x i8] c"()\0A\00", align 1
@.str225 = private constant [5 x i8] c"***\0A\00", align 1
@.str326 = private constant [4 x i8] c"%d\0A\00", align 1
@perm = internal global [351 x %struct.BASKET*] zeroinitializer, align 32
@initialize = internal global i64 1
@basket = internal global [351 x %struct.BASKET] zeroinitializer, align 32
@nr_group = internal global i64 0
@group_pos = internal global i64 0
@basket_size = internal global i64 0
@.str30 = private constant [2 x i8] c"r\00", align 1
@.str131 = private constant [8 x i8] c"%ld %ld\00", align 1
@.str232 = private constant [20 x i8] c"net->max_new_m >= 3\00", align 1
@.str333 = private constant [10 x i8] c"readmin.c\00", align 1
@__PRETTY_FUNCTION__.4370 = internal constant [9 x i8] c"read_min\00"
@.str434 = private constant [30 x i8] c"read_min(): not enough memory\00", align 1
@.str535 = private constant [12 x i8] c"%ld %ld %ld\00", align 1

define i64 @resize_prob(%struct.network_t* %net) nounwind {
entry:
  %net_addr = alloca %struct.network_t*, align 8
  %retval = alloca i64
  %0 = alloca i64
  %arc = alloca %struct.arc*
  %node = alloca %struct.node*
  %stop = alloca %struct.node*
  %root = alloca %struct.node*
  %off = alloca i64
  %"alloca point" = bitcast i32 0 to i32
  store %struct.network_t* %net, %struct.network_t** %net_addr
  %1 = load %struct.network_t** %net_addr, align 8
  %2 = getelementptr inbounds %struct.network_t* %1, i32 0, i32 9
  %3 = load i64* %2, align 8
  %4 = icmp sle i64 %3, 2
  br i1 %4, label %bb, label %bb1

bb:                                               ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([20 x i8]* @.str, i64 0, i64 0), i8* getelementptr inbounds ([11 x i8]* @.str1, i64 0, i64 0), i32 39, i8* getelementptr inbounds ([12 x i8]* @__PRETTY_FUNCTION__.4371, i64 0, i64 0)) noreturn nounwind
  unreachable

bb1:                                              ; preds = %entry
  %5 = load %struct.network_t** %net_addr, align 8
  %6 = getelementptr inbounds %struct.network_t* %5, i32 0, i32 4
  %7 = load i64* %6, align 8
  %8 = load %struct.network_t** %net_addr, align 8
  %9 = getelementptr inbounds %struct.network_t* %8, i32 0, i32 9
  %10 = load i64* %9, align 8
  %11 = add nsw i64 %7, %10
  %12 = load %struct.network_t** %net_addr, align 8
  %13 = getelementptr inbounds %struct.network_t* %12, i32 0, i32 4
  store i64 %11, i64* %13, align 8
  %14 = load %struct.network_t** %net_addr, align 8
  %15 = getelementptr inbounds %struct.network_t* %14, i32 0, i32 8
  %16 = load i64* %15, align 8
  %17 = load %struct.network_t** %net_addr, align 8
  %18 = getelementptr inbounds %struct.network_t* %17, i32 0, i32 9
  %19 = load i64* %18, align 8
  %20 = add nsw i64 %16, %19
  %21 = load %struct.network_t** %net_addr, align 8
  %22 = getelementptr inbounds %struct.network_t* %21, i32 0, i32 8
  store i64 %20, i64* %22, align 8
  %23 = load %struct.network_t** %net_addr, align 8
  %24 = getelementptr inbounds %struct.network_t* %23, i32 0, i32 4
  %25 = load i64* %24, align 8
  %26 = mul i64 %25, 64
  %27 = load %struct.network_t** %net_addr, align 8
  %28 = getelementptr inbounds %struct.network_t* %27, i32 0, i32 23
  %29 = load %struct.arc** %28, align 8
  %30 = bitcast %struct.arc* %29 to i8*
  %31 = call i8* @realloc(i8* %30, i64 %26) nounwind
  %32 = bitcast i8* %31 to %struct.arc*
  store %struct.arc* %32, %struct.arc** %arc, align 8
  %33 = load %struct.arc** %arc, align 8
  %34 = icmp eq %struct.arc* %33, null
  br i1 %34, label %bb2, label %bb3

bb2:                                              ; preds = %bb1
  %35 = load %struct.network_t** %net_addr, align 8
  %36 = getelementptr inbounds %struct.network_t* %35, i32 0, i32 0
  %37 = getelementptr inbounds [200 x i8]* %36, i64 0, i64 0
  %38 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([31 x i8]* @.str2, i64 0, i64 0), i8* %37) nounwind
  %39 = load %struct.FILE** @stdout, align 8
  %40 = call i32 @fflush(%struct.FILE* %39) nounwind
  store i64 -1, i64* %0, align 8
  br label %bb9

bb3:                                              ; preds = %bb1
  %41 = load %struct.arc** %arc, align 8
  %42 = ptrtoint %struct.arc* %41 to i64
  %43 = load %struct.network_t** %net_addr, align 8
  %44 = getelementptr inbounds %struct.network_t* %43, i32 0, i32 23
  %45 = load %struct.arc** %44, align 8
  %46 = ptrtoint %struct.arc* %45 to i64
  %47 = sub i64 %42, %46
  store i64 %47, i64* %off, align 8
  %48 = load %struct.network_t** %net_addr, align 8
  %49 = getelementptr inbounds %struct.network_t* %48, i32 0, i32 23
  %50 = load %struct.arc** %arc, align 8
  store %struct.arc* %50, %struct.arc** %49, align 8
  %51 = load %struct.network_t** %net_addr, align 8
  %52 = getelementptr inbounds %struct.network_t* %51, i32 0, i32 5
  %53 = load i64* %52, align 8
  %54 = load %struct.arc** %arc, align 8
  %55 = getelementptr inbounds %struct.arc* %54, i64 %53
  %56 = load %struct.network_t** %net_addr, align 8
  %57 = getelementptr inbounds %struct.network_t* %56, i32 0, i32 24
  store %struct.arc* %55, %struct.arc** %57, align 8
  %58 = load %struct.network_t** %net_addr, align 8
  %59 = getelementptr inbounds %struct.network_t* %58, i32 0, i32 21
  %60 = load %struct.node** %59, align 8
  store %struct.node* %60, %struct.node** %node, align 8
  %61 = load %struct.node** %node, align 8
  store %struct.node* %61, %struct.node** %root, align 8
  %62 = load %struct.node** %node, align 8
  %63 = getelementptr inbounds %struct.node* %62, i64 1
  store %struct.node* %63, %struct.node** %node, align 8
  %64 = load %struct.network_t** %net_addr, align 8
  %65 = getelementptr inbounds %struct.network_t* %64, i32 0, i32 22
  %66 = load %struct.node** %65, align 8
  store %struct.node* %66, %struct.node** %stop, align 8
  br label %bb7

bb4:                                              ; preds = %bb7
  %67 = load %struct.node** %node, align 8
  %68 = getelementptr inbounds %struct.node* %67, i32 0, i32 3
  %69 = load %struct.node** %68, align 8
  %70 = load %struct.node** %root, align 8
  %71 = icmp ne %struct.node* %69, %70
  br i1 %71, label %bb5, label %bb6

bb5:                                              ; preds = %bb4
  %72 = load %struct.node** %node, align 8
  %73 = getelementptr inbounds %struct.node* %72, i32 0, i32 6
  %74 = load %struct.arc** %73, align 8
  %75 = ptrtoint %struct.arc* %74 to i64
  %76 = load i64* %off, align 8
  %77 = add i64 %75, %76
  %78 = inttoptr i64 %77 to %struct.arc*
  %79 = load %struct.node** %node, align 8
  %80 = getelementptr inbounds %struct.node* %79, i32 0, i32 6
  store %struct.arc* %78, %struct.arc** %80, align 8
  br label %bb6

bb6:                                              ; preds = %bb5, %bb4
  %81 = load %struct.node** %node, align 8
  %82 = getelementptr inbounds %struct.node* %81, i64 1
  store %struct.node* %82, %struct.node** %node, align 8
  br label %bb7

bb7:                                              ; preds = %bb6, %bb3
  %83 = load %struct.node** %node, align 8
  %84 = load %struct.node** %stop, align 8
  %85 = icmp ult %struct.node* %83, %84
  br i1 %85, label %bb4, label %bb8

bb8:                                              ; preds = %bb7
  store i64 0, i64* %0, align 8
  br label %bb9

bb9:                                              ; preds = %bb8, %bb2
  %86 = load i64* %0, align 8
  store i64 %86, i64* %retval, align 8
  br label %return

return:                                           ; preds = %bb9
  %retval10 = load i64* %retval
  ret i64 %retval10
}

declare void @__assert_fail(i8*, i8*, i32, i8*) noreturn nounwind

declare i8* @realloc(i8*, i64) nounwind

declare i32 @printf(i8* noalias, ...) nounwind

declare i32 @fflush(%struct.FILE*)

define void @insert_new_arc(%struct.arc* %new, i64 %newpos, %struct.node* %tail, %struct.node* %head, i64 %cost, i64 %red_cost) nounwind {
entry:
  %new_addr = alloca %struct.arc*, align 8
  %newpos_addr = alloca i64, align 8
  %tail_addr = alloca %struct.node*, align 8
  %head_addr = alloca %struct.node*, align 8
  %cost_addr = alloca i64, align 8
  %red_cost_addr = alloca i64, align 8
  %pos = alloca i64
  %"alloca point" = bitcast i32 0 to i32
  store %struct.arc* %new, %struct.arc** %new_addr
  store i64 %newpos, i64* %newpos_addr
  store %struct.node* %tail, %struct.node** %tail_addr
  store %struct.node* %head, %struct.node** %head_addr
  store i64 %cost, i64* %cost_addr
  store i64 %red_cost, i64* %red_cost_addr
  %0 = load %struct.arc** %new_addr, align 8
  %1 = load i64* %newpos_addr, align 8
  %2 = getelementptr inbounds %struct.arc* %0, i64 %1
  %3 = getelementptr inbounds %struct.arc* %2, i32 0, i32 1
  %4 = load %struct.node** %tail_addr, align 8
  store %struct.node* %4, %struct.node** %3, align 8
  %5 = load %struct.arc** %new_addr, align 8
  %6 = load i64* %newpos_addr, align 8
  %7 = getelementptr inbounds %struct.arc* %5, i64 %6
  %8 = getelementptr inbounds %struct.arc* %7, i32 0, i32 2
  %9 = load %struct.node** %head_addr, align 8
  store %struct.node* %9, %struct.node** %8, align 8
  %10 = load %struct.arc** %new_addr, align 8
  %11 = load i64* %newpos_addr, align 8
  %12 = getelementptr inbounds %struct.arc* %10, i64 %11
  %13 = getelementptr inbounds %struct.arc* %12, i32 0, i32 7
  %14 = load i64* %cost_addr, align 8
  store i64 %14, i64* %13, align 8
  %15 = load %struct.arc** %new_addr, align 8
  %16 = load i64* %newpos_addr, align 8
  %17 = getelementptr inbounds %struct.arc* %15, i64 %16
  %18 = getelementptr inbounds %struct.arc* %17, i32 0, i32 0
  %19 = load i64* %cost_addr, align 8
  store i64 %19, i64* %18, align 8
  %20 = load %struct.arc** %new_addr, align 8
  %21 = load i64* %newpos_addr, align 8
  %22 = getelementptr inbounds %struct.arc* %20, i64 %21
  %23 = getelementptr inbounds %struct.arc* %22, i32 0, i32 6
  %24 = load i64* %red_cost_addr, align 8
  store i64 %24, i64* %23, align 8
  %25 = load i64* %newpos_addr, align 8
  %26 = add nsw i64 %25, 1
  store i64 %26, i64* %pos, align 8
  br label %bb1

bb:                                               ; preds = %bb2
  %27 = load i64* %pos, align 8
  %28 = sub nsw i64 %27, 1
  %29 = load %struct.arc** %new_addr, align 8
  %30 = getelementptr inbounds %struct.arc* %29, i64 %28
  %31 = load i64* %pos, align 8
  %32 = sdiv i64 %31, 2
  %33 = sub nsw i64 %32, 1
  %34 = load %struct.arc** %new_addr, align 8
  %35 = getelementptr inbounds %struct.arc* %34, i64 %33
  %36 = getelementptr inbounds %struct.arc* %35, i32 0, i32 1
  %37 = load %struct.node** %36, align 8
  %38 = getelementptr inbounds %struct.arc* %30, i32 0, i32 1
  store %struct.node* %37, %struct.node** %38, align 8
  %39 = load i64* %pos, align 8
  %40 = sub nsw i64 %39, 1
  %41 = load %struct.arc** %new_addr, align 8
  %42 = getelementptr inbounds %struct.arc* %41, i64 %40
  %43 = load i64* %pos, align 8
  %44 = sdiv i64 %43, 2
  %45 = sub nsw i64 %44, 1
  %46 = load %struct.arc** %new_addr, align 8
  %47 = getelementptr inbounds %struct.arc* %46, i64 %45
  %48 = getelementptr inbounds %struct.arc* %47, i32 0, i32 2
  %49 = load %struct.node** %48, align 8
  %50 = getelementptr inbounds %struct.arc* %42, i32 0, i32 2
  store %struct.node* %49, %struct.node** %50, align 8
  %51 = load i64* %pos, align 8
  %52 = sub nsw i64 %51, 1
  %53 = load %struct.arc** %new_addr, align 8
  %54 = getelementptr inbounds %struct.arc* %53, i64 %52
  %55 = load i64* %pos, align 8
  %56 = sdiv i64 %55, 2
  %57 = sub nsw i64 %56, 1
  %58 = load %struct.arc** %new_addr, align 8
  %59 = getelementptr inbounds %struct.arc* %58, i64 %57
  %60 = getelementptr inbounds %struct.arc* %59, i32 0, i32 0
  %61 = load i64* %60, align 8
  %62 = getelementptr inbounds %struct.arc* %54, i32 0, i32 0
  store i64 %61, i64* %62, align 8
  %63 = load i64* %pos, align 8
  %64 = sub nsw i64 %63, 1
  %65 = load %struct.arc** %new_addr, align 8
  %66 = getelementptr inbounds %struct.arc* %65, i64 %64
  %67 = load i64* %pos, align 8
  %68 = sdiv i64 %67, 2
  %69 = sub nsw i64 %68, 1
  %70 = load %struct.arc** %new_addr, align 8
  %71 = getelementptr inbounds %struct.arc* %70, i64 %69
  %72 = getelementptr inbounds %struct.arc* %71, i32 0, i32 0
  %73 = load i64* %72, align 8
  %74 = getelementptr inbounds %struct.arc* %66, i32 0, i32 7
  store i64 %73, i64* %74, align 8
  %75 = load i64* %pos, align 8
  %76 = sub nsw i64 %75, 1
  %77 = load %struct.arc** %new_addr, align 8
  %78 = getelementptr inbounds %struct.arc* %77, i64 %76
  %79 = load i64* %pos, align 8
  %80 = sdiv i64 %79, 2
  %81 = sub nsw i64 %80, 1
  %82 = load %struct.arc** %new_addr, align 8
  %83 = getelementptr inbounds %struct.arc* %82, i64 %81
  %84 = getelementptr inbounds %struct.arc* %83, i32 0, i32 6
  %85 = load i64* %84, align 8
  %86 = getelementptr inbounds %struct.arc* %78, i32 0, i32 6
  store i64 %85, i64* %86, align 8
  %87 = load i64* %pos, align 8
  %88 = sdiv i64 %87, 2
  store i64 %88, i64* %pos, align 8
  %89 = load i64* %pos, align 8
  %90 = sub nsw i64 %89, 1
  %91 = load %struct.arc** %new_addr, align 8
  %92 = getelementptr inbounds %struct.arc* %91, i64 %90
  %93 = getelementptr inbounds %struct.arc* %92, i32 0, i32 1
  %94 = load %struct.node** %tail_addr, align 8
  store %struct.node* %94, %struct.node** %93, align 8
  %95 = load i64* %pos, align 8
  %96 = sub nsw i64 %95, 1
  %97 = load %struct.arc** %new_addr, align 8
  %98 = getelementptr inbounds %struct.arc* %97, i64 %96
  %99 = getelementptr inbounds %struct.arc* %98, i32 0, i32 2
  %100 = load %struct.node** %head_addr, align 8
  store %struct.node* %100, %struct.node** %99, align 8
  %101 = load i64* %pos, align 8
  %102 = sub nsw i64 %101, 1
  %103 = load %struct.arc** %new_addr, align 8
  %104 = getelementptr inbounds %struct.arc* %103, i64 %102
  %105 = getelementptr inbounds %struct.arc* %104, i32 0, i32 0
  %106 = load i64* %cost_addr, align 8
  store i64 %106, i64* %105, align 8
  %107 = load i64* %pos, align 8
  %108 = sub nsw i64 %107, 1
  %109 = load %struct.arc** %new_addr, align 8
  %110 = getelementptr inbounds %struct.arc* %109, i64 %108
  %111 = getelementptr inbounds %struct.arc* %110, i32 0, i32 7
  %112 = load i64* %cost_addr, align 8
  store i64 %112, i64* %111, align 8
  %113 = load i64* %pos, align 8
  %114 = sub nsw i64 %113, 1
  %115 = load %struct.arc** %new_addr, align 8
  %116 = getelementptr inbounds %struct.arc* %115, i64 %114
  %117 = getelementptr inbounds %struct.arc* %116, i32 0, i32 6
  %118 = load i64* %red_cost_addr, align 8
  store i64 %118, i64* %117, align 8
  br label %bb1

bb1:                                              ; preds = %bb, %entry
  %119 = load i64* %pos, align 8
  %120 = icmp eq i64 %119, 1
  br i1 %120, label %bb3, label %bb2

bb2:                                              ; preds = %bb1
  %121 = load i64* %pos, align 8
  %122 = sdiv i64 %121, 2
  %123 = sub nsw i64 %122, 1
  %124 = load %struct.arc** %new_addr, align 8
  %125 = getelementptr inbounds %struct.arc* %124, i64 %123
  %126 = getelementptr inbounds %struct.arc* %125, i32 0, i32 6
  %127 = load i64* %126, align 8
  %128 = load i64* %red_cost_addr, align 8
  %129 = icmp slt i64 %127, %128
  br i1 %129, label %bb, label %bb3

bb3:                                              ; preds = %bb2, %bb1
  br label %return

return:                                           ; preds = %bb3
  ret void
}

define void @replace_weaker_arc(%struct.network_t* %net, %struct.arc* %new, %struct.node* %tail, %struct.node* %head, i64 %cost, i64 %red_cost) nounwind {
entry:
  %net_addr = alloca %struct.network_t*, align 8
  %new_addr = alloca %struct.arc*, align 8
  %tail_addr = alloca %struct.node*, align 8
  %head_addr = alloca %struct.node*, align 8
  %cost_addr = alloca i64, align 8
  %red_cost_addr = alloca i64, align 8
  %iftmp.3 = alloca i64
  %pos = alloca i64
  %cmp = alloca i64
  %"alloca point" = bitcast i32 0 to i32
  store %struct.network_t* %net, %struct.network_t** %net_addr
  store %struct.arc* %new, %struct.arc** %new_addr
  store %struct.node* %tail, %struct.node** %tail_addr
  store %struct.node* %head, %struct.node** %head_addr
  store i64 %cost, i64* %cost_addr
  store i64 %red_cost, i64* %red_cost_addr
  %0 = load %struct.arc** %new_addr, align 8
  %1 = getelementptr inbounds %struct.arc* %0, i64 0
  %2 = getelementptr inbounds %struct.arc* %1, i32 0, i32 1
  %3 = load %struct.node** %tail_addr, align 8
  store %struct.node* %3, %struct.node** %2, align 8
  %4 = load %struct.arc** %new_addr, align 8
  %5 = getelementptr inbounds %struct.arc* %4, i64 0
  %6 = getelementptr inbounds %struct.arc* %5, i32 0, i32 2
  %7 = load %struct.node** %head_addr, align 8
  store %struct.node* %7, %struct.node** %6, align 8
  %8 = load %struct.arc** %new_addr, align 8
  %9 = getelementptr inbounds %struct.arc* %8, i64 0
  %10 = getelementptr inbounds %struct.arc* %9, i32 0, i32 7
  %11 = load i64* %cost_addr, align 8
  store i64 %11, i64* %10, align 8
  %12 = load %struct.arc** %new_addr, align 8
  %13 = getelementptr inbounds %struct.arc* %12, i64 0
  %14 = getelementptr inbounds %struct.arc* %13, i32 0, i32 0
  %15 = load i64* %cost_addr, align 8
  store i64 %15, i64* %14, align 8
  %16 = load %struct.arc** %new_addr, align 8
  %17 = getelementptr inbounds %struct.arc* %16, i64 0
  %18 = getelementptr inbounds %struct.arc* %17, i32 0, i32 6
  %19 = load i64* %red_cost_addr, align 8
  store i64 %19, i64* %18, align 8
  store i64 1, i64* %pos, align 8
  %20 = load %struct.arc** %new_addr, align 8
  %21 = getelementptr inbounds %struct.arc* %20, i64 1
  %22 = getelementptr inbounds %struct.arc* %21, i32 0, i32 6
  %23 = load i64* %22, align 8
  %24 = load %struct.arc** %new_addr, align 8
  %25 = getelementptr inbounds %struct.arc* %24, i64 2
  %26 = getelementptr inbounds %struct.arc* %25, i32 0, i32 6
  %27 = load i64* %26, align 8
  %28 = icmp sgt i64 %23, %27
  br i1 %28, label %bb, label %bb1

bb:                                               ; preds = %entry
  store i64 2, i64* %iftmp.3, align 8
  br label %bb2

bb1:                                              ; preds = %entry
  store i64 3, i64* %iftmp.3, align 8
  br label %bb2

bb2:                                              ; preds = %bb1, %bb
  %29 = load i64* %iftmp.3, align 8
  store i64 %29, i64* %cmp, align 8
  br label %bb6

bb3:                                              ; preds = %bb7
  %30 = load i64* %pos, align 8
  %31 = sub nsw i64 %30, 1
  %32 = load %struct.arc** %new_addr, align 8
  %33 = getelementptr inbounds %struct.arc* %32, i64 %31
  %34 = load i64* %cmp, align 8
  %35 = sub nsw i64 %34, 1
  %36 = load %struct.arc** %new_addr, align 8
  %37 = getelementptr inbounds %struct.arc* %36, i64 %35
  %38 = getelementptr inbounds %struct.arc* %37, i32 0, i32 1
  %39 = load %struct.node** %38, align 8
  %40 = getelementptr inbounds %struct.arc* %33, i32 0, i32 1
  store %struct.node* %39, %struct.node** %40, align 8
  %41 = load i64* %pos, align 8
  %42 = sub nsw i64 %41, 1
  %43 = load %struct.arc** %new_addr, align 8
  %44 = getelementptr inbounds %struct.arc* %43, i64 %42
  %45 = load i64* %cmp, align 8
  %46 = sub nsw i64 %45, 1
  %47 = load %struct.arc** %new_addr, align 8
  %48 = getelementptr inbounds %struct.arc* %47, i64 %46
  %49 = getelementptr inbounds %struct.arc* %48, i32 0, i32 2
  %50 = load %struct.node** %49, align 8
  %51 = getelementptr inbounds %struct.arc* %44, i32 0, i32 2
  store %struct.node* %50, %struct.node** %51, align 8
  %52 = load i64* %pos, align 8
  %53 = sub nsw i64 %52, 1
  %54 = load %struct.arc** %new_addr, align 8
  %55 = getelementptr inbounds %struct.arc* %54, i64 %53
  %56 = load i64* %cmp, align 8
  %57 = sub nsw i64 %56, 1
  %58 = load %struct.arc** %new_addr, align 8
  %59 = getelementptr inbounds %struct.arc* %58, i64 %57
  %60 = getelementptr inbounds %struct.arc* %59, i32 0, i32 0
  %61 = load i64* %60, align 8
  %62 = getelementptr inbounds %struct.arc* %55, i32 0, i32 0
  store i64 %61, i64* %62, align 8
  %63 = load i64* %pos, align 8
  %64 = sub nsw i64 %63, 1
  %65 = load %struct.arc** %new_addr, align 8
  %66 = getelementptr inbounds %struct.arc* %65, i64 %64
  %67 = load i64* %cmp, align 8
  %68 = sub nsw i64 %67, 1
  %69 = load %struct.arc** %new_addr, align 8
  %70 = getelementptr inbounds %struct.arc* %69, i64 %68
  %71 = getelementptr inbounds %struct.arc* %70, i32 0, i32 0
  %72 = load i64* %71, align 8
  %73 = getelementptr inbounds %struct.arc* %66, i32 0, i32 7
  store i64 %72, i64* %73, align 8
  %74 = load i64* %pos, align 8
  %75 = sub nsw i64 %74, 1
  %76 = load %struct.arc** %new_addr, align 8
  %77 = getelementptr inbounds %struct.arc* %76, i64 %75
  %78 = load i64* %cmp, align 8
  %79 = sub nsw i64 %78, 1
  %80 = load %struct.arc** %new_addr, align 8
  %81 = getelementptr inbounds %struct.arc* %80, i64 %79
  %82 = getelementptr inbounds %struct.arc* %81, i32 0, i32 6
  %83 = load i64* %82, align 8
  %84 = getelementptr inbounds %struct.arc* %77, i32 0, i32 6
  store i64 %83, i64* %84, align 8
  %85 = load i64* %cmp, align 8
  %86 = sub nsw i64 %85, 1
  %87 = load %struct.arc** %new_addr, align 8
  %88 = getelementptr inbounds %struct.arc* %87, i64 %86
  %89 = getelementptr inbounds %struct.arc* %88, i32 0, i32 1
  %90 = load %struct.node** %tail_addr, align 8
  store %struct.node* %90, %struct.node** %89, align 8
  %91 = load i64* %cmp, align 8
  %92 = sub nsw i64 %91, 1
  %93 = load %struct.arc** %new_addr, align 8
  %94 = getelementptr inbounds %struct.arc* %93, i64 %92
  %95 = getelementptr inbounds %struct.arc* %94, i32 0, i32 2
  %96 = load %struct.node** %head_addr, align 8
  store %struct.node* %96, %struct.node** %95, align 8
  %97 = load i64* %cmp, align 8
  %98 = sub nsw i64 %97, 1
  %99 = load %struct.arc** %new_addr, align 8
  %100 = getelementptr inbounds %struct.arc* %99, i64 %98
  %101 = getelementptr inbounds %struct.arc* %100, i32 0, i32 0
  %102 = load i64* %cost_addr, align 8
  store i64 %102, i64* %101, align 8
  %103 = load i64* %cmp, align 8
  %104 = sub nsw i64 %103, 1
  %105 = load %struct.arc** %new_addr, align 8
  %106 = getelementptr inbounds %struct.arc* %105, i64 %104
  %107 = getelementptr inbounds %struct.arc* %106, i32 0, i32 7
  %108 = load i64* %cost_addr, align 8
  store i64 %108, i64* %107, align 8
  %109 = load i64* %cmp, align 8
  %110 = sub nsw i64 %109, 1
  %111 = load %struct.arc** %new_addr, align 8
  %112 = getelementptr inbounds %struct.arc* %111, i64 %110
  %113 = getelementptr inbounds %struct.arc* %112, i32 0, i32 6
  %114 = load i64* %red_cost_addr, align 8
  store i64 %114, i64* %113, align 8
  %115 = load i64* %cmp, align 8
  store i64 %115, i64* %pos, align 8
  %116 = load i64* %cmp, align 8
  %117 = mul nsw i64 %116, 2
  store i64 %117, i64* %cmp, align 8
  %118 = load i64* %cmp, align 8
  %119 = add nsw i64 %118, 1
  %120 = load %struct.network_t** %net_addr, align 8
  %121 = getelementptr inbounds %struct.network_t* %120, i32 0, i32 8
  %122 = load i64* %121, align 8
  %123 = icmp sle i64 %119, %122
  br i1 %123, label %bb4, label %bb6

bb4:                                              ; preds = %bb3
  %124 = load i64* %cmp, align 8
  %125 = sub nsw i64 %124, 1
  %126 = load %struct.arc** %new_addr, align 8
  %127 = getelementptr inbounds %struct.arc* %126, i64 %125
  %128 = getelementptr inbounds %struct.arc* %127, i32 0, i32 6
  %129 = load i64* %128, align 8
  %130 = load %struct.arc** %new_addr, align 8
  %131 = load i64* %cmp, align 8
  %132 = getelementptr inbounds %struct.arc* %130, i64 %131
  %133 = getelementptr inbounds %struct.arc* %132, i32 0, i32 6
  %134 = load i64* %133, align 8
  %135 = icmp slt i64 %129, %134
  br i1 %135, label %bb5, label %bb6

bb5:                                              ; preds = %bb4
  %136 = load i64* %cmp, align 8
  %137 = add nsw i64 %136, 1
  store i64 %137, i64* %cmp, align 8
  br label %bb6

bb6:                                              ; preds = %bb5, %bb4, %bb3, %bb2
  %138 = load %struct.network_t** %net_addr, align 8
  %139 = getelementptr inbounds %struct.network_t* %138, i32 0, i32 8
  %140 = load i64* %139, align 8
  %141 = load i64* %cmp, align 8
  %142 = icmp slt i64 %140, %141
  br i1 %142, label %bb8, label %bb7

bb7:                                              ; preds = %bb6
  %143 = load i64* %cmp, align 8
  %144 = sub nsw i64 %143, 1
  %145 = load %struct.arc** %new_addr, align 8
  %146 = getelementptr inbounds %struct.arc* %145, i64 %144
  %147 = getelementptr inbounds %struct.arc* %146, i32 0, i32 6
  %148 = load i64* %147, align 8
  %149 = load i64* %red_cost_addr, align 8
  %150 = icmp sgt i64 %148, %149
  br i1 %150, label %bb3, label %bb8

bb8:                                              ; preds = %bb7, %bb6
  br label %return

return:                                           ; preds = %bb8
  ret void
}

define i64 @price_out_impl(%struct.network_t* %net) nounwind {
entry:
  %net_addr = alloca %struct.network_t*, align 8
  %retval = alloca i64
  %0 = alloca i64
  %i = alloca i64
  %trips = alloca i64
  %new_arcs = alloca i64
  %resized = alloca i64
  %latest = alloca i64
  %min_impl_duration = alloca i64
  %bigM = alloca i64
  %head_potential = alloca i64
  %arc_cost = alloca i64
  %red_cost = alloca i64
  %bigM_minus_min_impl_duration = alloca i64
  %arcout = alloca %struct.arc*
  %arcin = alloca %struct.arc*
  %arcnew = alloca %struct.arc*
  %stop = alloca %struct.arc*
  %first_of_sparse_list = alloca %struct.arc*
  %tail = alloca %struct.node*
  %head = alloca %struct.node*
  %"alloca point" = bitcast i32 0 to i32
  store %struct.network_t* %net, %struct.network_t** %net_addr
  store i64 0, i64* %new_arcs, align 8
  store i64 0, i64* %resized, align 8
  store i64 15, i64* %min_impl_duration, align 8
  %1 = load %struct.network_t** %net_addr, align 8
  %2 = getelementptr inbounds %struct.network_t* %1, i32 0, i32 18
  %3 = load i64* %2, align 8
  store i64 %3, i64* %bigM, align 8
  store i64 30, i64* %arc_cost, align 8
  %4 = load i64* %bigM, align 8
  %5 = load i64* %min_impl_duration, align 8
  %6 = sub nsw i64 %4, %5
  store i64 %6, i64* %bigM_minus_min_impl_duration, align 8
  %7 = load %struct.network_t** %net_addr, align 8
  %8 = getelementptr inbounds %struct.network_t* %7, i32 0, i32 3
  %9 = load i64* %8, align 8
  %10 = icmp sle i64 %9, 15000
  br i1 %10, label %bb, label %bb5

bb:                                               ; preds = %entry
  %11 = load %struct.network_t** %net_addr, align 8
  %12 = getelementptr inbounds %struct.network_t* %11, i32 0, i32 5
  %13 = load i64* %12, align 8
  %14 = load %struct.network_t** %net_addr, align 8
  %15 = getelementptr inbounds %struct.network_t* %14, i32 0, i32 9
  %16 = load i64* %15, align 8
  %17 = add nsw i64 %13, %16
  %18 = load %struct.network_t** %net_addr, align 8
  %19 = getelementptr inbounds %struct.network_t* %18, i32 0, i32 4
  %20 = load i64* %19, align 8
  %21 = icmp sgt i64 %17, %20
  br i1 %21, label %bb1, label %bb5

bb1:                                              ; preds = %bb
  %22 = load %struct.network_t** %net_addr, align 8
  %23 = getelementptr inbounds %struct.network_t* %22, i32 0, i32 3
  %24 = load i64* %23, align 8
  %25 = load %struct.network_t** %net_addr, align 8
  %26 = getelementptr inbounds %struct.network_t* %25, i32 0, i32 3
  %27 = load i64* %26, align 8
  %28 = mul nsw i64 %24, %27
  %29 = sdiv i64 %28, 2
  %30 = load %struct.network_t** %net_addr, align 8
  %31 = getelementptr inbounds %struct.network_t* %30, i32 0, i32 5
  %32 = load i64* %31, align 8
  %33 = add nsw i64 %29, %32
  %34 = load %struct.network_t** %net_addr, align 8
  %35 = getelementptr inbounds %struct.network_t* %34, i32 0, i32 4
  %36 = load i64* %35, align 8
  %37 = icmp sgt i64 %33, %36
  br i1 %37, label %bb2, label %bb5

bb2:                                              ; preds = %bb1
  store i64 1, i64* %resized, align 8
  %38 = load %struct.network_t** %net_addr, align 8
  %39 = call i64 @resize_prob(%struct.network_t* %38) nounwind
  %40 = icmp ne i64 %39, 0
  br i1 %40, label %bb3, label %bb4

bb3:                                              ; preds = %bb2
  store i64 -1, i64* %0, align 8
  br label %bb36

bb4:                                              ; preds = %bb2
  %41 = load %struct.network_t** %net_addr, align 8
  call void @refresh_neighbour_lists(%struct.network_t* %41) nounwind
  br label %bb5

bb5:                                              ; preds = %bb4, %bb1, %bb, %entry
  %42 = load %struct.network_t** %net_addr, align 8
  %43 = getelementptr inbounds %struct.network_t* %42, i32 0, i32 24
  %44 = load %struct.arc** %43, align 8
  store %struct.arc* %44, %struct.arc** %arcnew, align 8
  %45 = load %struct.network_t** %net_addr, align 8
  %46 = getelementptr inbounds %struct.network_t* %45, i32 0, i32 3
  %47 = load i64* %46, align 8
  store i64 %47, i64* %trips, align 8
  %48 = load %struct.network_t** %net_addr, align 8
  %49 = getelementptr inbounds %struct.network_t* %48, i32 0, i32 23
  %50 = load %struct.arc** %49, align 8
  store %struct.arc* %50, %struct.arc** %arcout, align 8
  store i64 0, i64* %i, align 8
  br label %bb7

bb6:                                              ; preds = %bb8
  %51 = load i64* %i, align 8
  %52 = add nsw i64 %51, 1
  store i64 %52, i64* %i, align 8
  %53 = load %struct.arc** %arcout, align 8
  %54 = getelementptr inbounds %struct.arc* %53, i64 3
  store %struct.arc* %54, %struct.arc** %arcout, align 8
  br label %bb7

bb7:                                              ; preds = %bb6, %bb5
  %55 = load i64* %i, align 8
  %56 = load i64* %trips, align 8
  %57 = icmp sge i64 %55, %56
  br i1 %57, label %bb9, label %bb8

bb8:                                              ; preds = %bb7
  %58 = load %struct.arc** %arcout, align 8
  %59 = getelementptr inbounds %struct.arc* %58, i64 1
  %60 = getelementptr inbounds %struct.arc* %59, i32 0, i32 3
  %61 = load i32* %60, align 8
  %62 = icmp eq i32 %61, -1
  br i1 %62, label %bb6, label %bb9

bb9:                                              ; preds = %bb8, %bb7
  store %struct.arc* null, %struct.arc** %first_of_sparse_list, align 8
  br label %bb24

bb10:                                             ; preds = %bb24
  %63 = load %struct.arc** %arcout, align 8
  %64 = getelementptr inbounds %struct.arc* %63, i64 1
  %65 = getelementptr inbounds %struct.arc* %64, i32 0, i32 3
  %66 = load i32* %65, align 8
  %67 = icmp ne i32 %66, -1
  br i1 %67, label %bb11, label %bb12

bb11:                                             ; preds = %bb10
  %68 = load %struct.arc** %arcout, align 8
  %69 = getelementptr inbounds %struct.arc* %68, i32 0, i32 2
  %70 = load %struct.node** %69, align 8
  %71 = getelementptr inbounds %struct.node* %70, i32 0, i32 7
  %72 = load %struct.arc** %71, align 8
  %73 = getelementptr inbounds %struct.arc* %72, i32 0, i32 2
  %74 = load %struct.node** %73, align 8
  %75 = getelementptr inbounds %struct.node* %74, i32 0, i32 9
  %76 = load %struct.arc** %first_of_sparse_list, align 8
  store %struct.arc* %76, %struct.arc** %75, align 8
  %77 = load %struct.arc** %arcout, align 8
  %78 = getelementptr inbounds %struct.arc* %77, i64 1
  store %struct.arc* %78, %struct.arc** %first_of_sparse_list, align 8
  br label %bb12

bb12:                                             ; preds = %bb11, %bb10
  %79 = load %struct.arc** %arcout, align 8
  %80 = getelementptr inbounds %struct.arc* %79, i32 0, i32 3
  %81 = load i32* %80, align 8
  %82 = icmp eq i32 %81, -1
  br i1 %82, label %bb23, label %bb13

bb13:                                             ; preds = %bb12
  %83 = load %struct.arc** %arcout, align 8
  %84 = getelementptr inbounds %struct.arc* %83, i32 0, i32 2
  %85 = load %struct.node** %84, align 8
  store %struct.node* %85, %struct.node** %head, align 8
  %86 = load %struct.node** %head, align 8
  %87 = getelementptr inbounds %struct.node* %86, i32 0, i32 13
  %88 = load i32* %87, align 4
  %89 = sext i32 %88 to i64
  %90 = load %struct.arc** %arcout, align 8
  %91 = getelementptr inbounds %struct.arc* %90, i32 0, i32 7
  %92 = load i64* %91, align 8
  %93 = sub nsw i64 %89, %92
  %94 = load i64* %bigM_minus_min_impl_duration, align 8
  %95 = add nsw i64 %93, %94
  store i64 %95, i64* %latest, align 8
  %96 = load %struct.node** %head, align 8
  %97 = getelementptr inbounds %struct.node* %96, i32 0, i32 0
  %98 = load i64* %97, align 8
  store i64 %98, i64* %head_potential, align 8
  %99 = load %struct.arc** %first_of_sparse_list, align 8
  %100 = getelementptr inbounds %struct.arc* %99, i32 0, i32 1
  %101 = load %struct.node** %100, align 8
  %102 = getelementptr inbounds %struct.node* %101, i32 0, i32 9
  %103 = load %struct.arc** %102, align 8
  store %struct.arc* %103, %struct.arc** %arcin, align 8
  br label %bb22

bb14:                                             ; preds = %bb22
  %104 = load %struct.arc** %arcin, align 8
  %105 = getelementptr inbounds %struct.arc* %104, i32 0, i32 1
  %106 = load %struct.node** %105, align 8
  store %struct.node* %106, %struct.node** %tail, align 8
  %107 = load %struct.node** %tail, align 8
  %108 = getelementptr inbounds %struct.node* %107, i32 0, i32 13
  %109 = load i32* %108, align 4
  %110 = sext i32 %109 to i64
  %111 = load %struct.arc** %arcin, align 8
  %112 = getelementptr inbounds %struct.arc* %111, i32 0, i32 7
  %113 = load i64* %112, align 8
  %114 = add nsw i64 %110, %113
  %115 = load i64* %latest, align 8
  %116 = icmp sgt i64 %114, %115
  br i1 %116, label %bb15, label %bb16

bb15:                                             ; preds = %bb14
  %117 = load %struct.node** %tail, align 8
  %118 = getelementptr inbounds %struct.node* %117, i32 0, i32 9
  %119 = load %struct.arc** %118, align 8
  store %struct.arc* %119, %struct.arc** %arcin, align 8
  br label %bb22

bb16:                                             ; preds = %bb14
  %120 = load %struct.node** %tail, align 8
  %121 = getelementptr inbounds %struct.node* %120, i32 0, i32 0
  %122 = load i64* %121, align 8
  %123 = load i64* %arc_cost, align 8
  %124 = sub nsw i64 %123, %122
  %125 = load %struct.node** %head, align 8
  %126 = getelementptr inbounds %struct.node* %125, i32 0, i32 0
  %127 = load i64* %126, align 8
  %128 = add nsw i64 %124, %127
  store i64 %128, i64* %red_cost, align 8
  %129 = load i64* %red_cost, align 8
  %130 = icmp slt i64 %129, 0
  br i1 %130, label %bb17, label %bb21

bb17:                                             ; preds = %bb16
  %131 = load %struct.network_t** %net_addr, align 8
  %132 = getelementptr inbounds %struct.network_t* %131, i32 0, i32 8
  %133 = load i64* %132, align 8
  %134 = load i64* %new_arcs, align 8
  %135 = icmp sgt i64 %133, %134
  br i1 %135, label %bb18, label %bb19

bb18:                                             ; preds = %bb17
  %136 = load %struct.arc** %arcnew, align 8
  %137 = load i64* %new_arcs, align 8
  %138 = load %struct.node** %tail, align 8
  %139 = load %struct.node** %head, align 8
  %140 = load i64* %arc_cost, align 8
  %141 = load i64* %red_cost, align 8
  call void @insert_new_arc(%struct.arc* %136, i64 %137, %struct.node* %138, %struct.node* %139, i64 %140, i64 %141) nounwind
  %142 = load i64* %new_arcs, align 8
  %143 = add nsw i64 %142, 1
  store i64 %143, i64* %new_arcs, align 8
  br label %bb21

bb19:                                             ; preds = %bb17
  %144 = load %struct.arc** %arcnew, align 8
  %145 = getelementptr inbounds %struct.arc* %144, i64 0
  %146 = getelementptr inbounds %struct.arc* %145, i32 0, i32 6
  %147 = load i64* %146, align 8
  %148 = load i64* %red_cost, align 8
  %149 = icmp sgt i64 %147, %148
  br i1 %149, label %bb20, label %bb21

bb20:                                             ; preds = %bb19
  %150 = load %struct.network_t** %net_addr, align 8
  %151 = load %struct.arc** %arcnew, align 8
  %152 = load %struct.node** %tail, align 8
  %153 = load %struct.node** %head, align 8
  %154 = load i64* %arc_cost, align 8
  %155 = load i64* %red_cost, align 8
  call void @replace_weaker_arc(%struct.network_t* %150, %struct.arc* %151, %struct.node* %152, %struct.node* %153, i64 %154, i64 %155) nounwind
  br label %bb21

bb21:                                             ; preds = %bb20, %bb19, %bb18, %bb16
  %156 = load %struct.node** %tail, align 8
  %157 = getelementptr inbounds %struct.node* %156, i32 0, i32 9
  %158 = load %struct.arc** %157, align 8
  store %struct.arc* %158, %struct.arc** %arcin, align 8
  br label %bb22

bb22:                                             ; preds = %bb21, %bb15, %bb13
  %159 = load %struct.arc** %arcin, align 8
  %160 = icmp ne %struct.arc* %159, null
  br i1 %160, label %bb14, label %bb23

bb23:                                             ; preds = %bb22, %bb12
  %161 = load i64* %i, align 8
  %162 = add nsw i64 %161, 1
  store i64 %162, i64* %i, align 8
  %163 = load %struct.arc** %arcout, align 8
  %164 = getelementptr inbounds %struct.arc* %163, i64 3
  store %struct.arc* %164, %struct.arc** %arcout, align 8
  br label %bb24

bb24:                                             ; preds = %bb23, %bb9
  %165 = load i64* %i, align 8
  %166 = load i64* %trips, align 8
  %167 = icmp slt i64 %165, %166
  br i1 %167, label %bb10, label %bb25

bb25:                                             ; preds = %bb24
  %168 = load i64* %new_arcs, align 8
  %169 = icmp ne i64 %168, 0
  br i1 %169, label %bb26, label %bb35

bb26:                                             ; preds = %bb25
  %170 = load %struct.network_t** %net_addr, align 8
  %171 = getelementptr inbounds %struct.network_t* %170, i32 0, i32 24
  %172 = load %struct.arc** %171, align 8
  store %struct.arc* %172, %struct.arc** %arcnew, align 8
  %173 = load %struct.network_t** %net_addr, align 8
  %174 = getelementptr inbounds %struct.network_t* %173, i32 0, i32 24
  %175 = load %struct.arc** %174, align 8
  %176 = load i64* %new_arcs, align 8
  %177 = getelementptr inbounds %struct.arc* %175, i64 %176
  %178 = load %struct.network_t** %net_addr, align 8
  %179 = getelementptr inbounds %struct.network_t* %178, i32 0, i32 24
  store %struct.arc* %177, %struct.arc** %179, align 8
  %180 = load %struct.network_t** %net_addr, align 8
  %181 = getelementptr inbounds %struct.network_t* %180, i32 0, i32 24
  %182 = load %struct.arc** %181, align 8
  store %struct.arc* %182, %struct.arc** %stop, align 8
  %183 = load i64* %resized, align 8
  %184 = icmp ne i64 %183, 0
  br i1 %184, label %bb27, label %bb31

bb27:                                             ; preds = %bb26
  br label %bb29

bb28:                                             ; preds = %bb29
  %185 = load %struct.arc** %arcnew, align 8
  %186 = getelementptr inbounds %struct.arc* %185, i32 0, i32 6
  store i64 0, i64* %186, align 8
  %187 = load %struct.arc** %arcnew, align 8
  %188 = getelementptr inbounds %struct.arc* %187, i32 0, i32 3
  store i32 1, i32* %188, align 8
  %189 = load %struct.arc** %arcnew, align 8
  %190 = getelementptr inbounds %struct.arc* %189, i64 1
  store %struct.arc* %190, %struct.arc** %arcnew, align 8
  br label %bb29

bb29:                                             ; preds = %bb28, %bb27
  %191 = load %struct.arc** %arcnew, align 8
  %192 = load %struct.arc** %stop, align 8
  %193 = icmp ne %struct.arc* %191, %192
  br i1 %193, label %bb28, label %bb30

bb30:                                             ; preds = %bb29
  br label %bb34

bb31:                                             ; preds = %bb26
  br label %bb33

bb32:                                             ; preds = %bb33
  %194 = load %struct.arc** %arcnew, align 8
  %195 = getelementptr inbounds %struct.arc* %194, i32 0, i32 6
  store i64 0, i64* %195, align 8
  %196 = load %struct.arc** %arcnew, align 8
  %197 = getelementptr inbounds %struct.arc* %196, i32 0, i32 3
  store i32 1, i32* %197, align 8
  %198 = load %struct.arc** %arcnew, align 8
  %199 = getelementptr inbounds %struct.arc* %198, i32 0, i32 1
  %200 = load %struct.node** %199, align 8
  %201 = getelementptr inbounds %struct.node* %200, i32 0, i32 7
  %202 = load %struct.arc** %201, align 8
  %203 = load %struct.arc** %arcnew, align 8
  %204 = getelementptr inbounds %struct.arc* %203, i32 0, i32 4
  store %struct.arc* %202, %struct.arc** %204, align 8
  %205 = load %struct.arc** %arcnew, align 8
  %206 = getelementptr inbounds %struct.arc* %205, i32 0, i32 1
  %207 = load %struct.node** %206, align 8
  %208 = getelementptr inbounds %struct.node* %207, i32 0, i32 7
  %209 = load %struct.arc** %arcnew, align 8
  store %struct.arc* %209, %struct.arc** %208, align 8
  %210 = load %struct.arc** %arcnew, align 8
  %211 = getelementptr inbounds %struct.arc* %210, i32 0, i32 2
  %212 = load %struct.node** %211, align 8
  %213 = getelementptr inbounds %struct.node* %212, i32 0, i32 8
  %214 = load %struct.arc** %213, align 8
  %215 = load %struct.arc** %arcnew, align 8
  %216 = getelementptr inbounds %struct.arc* %215, i32 0, i32 5
  store %struct.arc* %214, %struct.arc** %216, align 8
  %217 = load %struct.arc** %arcnew, align 8
  %218 = getelementptr inbounds %struct.arc* %217, i32 0, i32 2
  %219 = load %struct.node** %218, align 8
  %220 = getelementptr inbounds %struct.node* %219, i32 0, i32 8
  %221 = load %struct.arc** %arcnew, align 8
  store %struct.arc* %221, %struct.arc** %220, align 8
  %222 = load %struct.arc** %arcnew, align 8
  %223 = getelementptr inbounds %struct.arc* %222, i64 1
  store %struct.arc* %223, %struct.arc** %arcnew, align 8
  br label %bb33

bb33:                                             ; preds = %bb32, %bb31
  %224 = load %struct.arc** %arcnew, align 8
  %225 = load %struct.arc** %stop, align 8
  %226 = icmp ne %struct.arc* %224, %225
  br i1 %226, label %bb32, label %bb34

bb34:                                             ; preds = %bb33, %bb30
  %227 = load %struct.network_t** %net_addr, align 8
  %228 = getelementptr inbounds %struct.network_t* %227, i32 0, i32 5
  %229 = load i64* %228, align 8
  %230 = load i64* %new_arcs, align 8
  %231 = add nsw i64 %229, %230
  %232 = load %struct.network_t** %net_addr, align 8
  %233 = getelementptr inbounds %struct.network_t* %232, i32 0, i32 5
  store i64 %231, i64* %233, align 8
  %234 = load %struct.network_t** %net_addr, align 8
  %235 = getelementptr inbounds %struct.network_t* %234, i32 0, i32 7
  %236 = load i64* %235, align 8
  %237 = load i64* %new_arcs, align 8
  %238 = add nsw i64 %236, %237
  %239 = load %struct.network_t** %net_addr, align 8
  %240 = getelementptr inbounds %struct.network_t* %239, i32 0, i32 7
  store i64 %238, i64* %240, align 8
  %241 = load %struct.network_t** %net_addr, align 8
  %242 = getelementptr inbounds %struct.network_t* %241, i32 0, i32 8
  %243 = load i64* %242, align 8
  %244 = load i64* %new_arcs, align 8
  %245 = sub nsw i64 %243, %244
  %246 = load %struct.network_t** %net_addr, align 8
  %247 = getelementptr inbounds %struct.network_t* %246, i32 0, i32 8
  store i64 %245, i64* %247, align 8
  br label %bb35

bb35:                                             ; preds = %bb34, %bb25
  %248 = load i64* %new_arcs, align 8
  store i64 %248, i64* %0, align 8
  br label %bb36

bb36:                                             ; preds = %bb35, %bb3
  %249 = load i64* %0, align 8
  store i64 %249, i64* %retval, align 8
  br label %return

return:                                           ; preds = %bb36
  %retval37 = load i64* %retval
  ret i64 %retval37
}

define i64 @suspend_impl(%struct.network_t* %net, i64 %threshold, i64 %all) nounwind {
entry:
  %net_addr = alloca %struct.network_t*, align 8
  %threshold_addr = alloca i64, align 8
  %all_addr = alloca i64, align 8
  %retval = alloca i64
  %0 = alloca i64
  %susp = alloca i64
  %red_cost = alloca i64
  %new_arc = alloca %struct.arc*
  %arc = alloca %struct.arc*
  %stop = alloca i8*
  %"alloca point" = bitcast i32 0 to i32
  store %struct.network_t* %net, %struct.network_t** %net_addr
  store i64 %threshold, i64* %threshold_addr
  store i64 %all, i64* %all_addr
  %1 = load i64* %all_addr, align 8
  %2 = icmp ne i64 %1, 0
  br i1 %2, label %bb, label %bb1

bb:                                               ; preds = %entry
  %3 = load %struct.network_t** %net_addr, align 8
  %4 = getelementptr inbounds %struct.network_t* %3, i32 0, i32 7
  %5 = load i64* %4, align 8
  store i64 %5, i64* %susp, align 8
  br label %bb13

bb1:                                              ; preds = %entry
  %6 = load %struct.network_t** %net_addr, align 8
  %7 = getelementptr inbounds %struct.network_t* %6, i32 0, i32 24
  %8 = load %struct.arc** %7, align 8
  %9 = bitcast %struct.arc* %8 to i8*
  store i8* %9, i8** %stop, align 8
  %10 = load %struct.network_t** %net_addr, align 8
  %11 = getelementptr inbounds %struct.network_t* %10, i32 0, i32 23
  %12 = load %struct.arc** %11, align 8
  %13 = load %struct.network_t** %net_addr, align 8
  %14 = getelementptr inbounds %struct.network_t* %13, i32 0, i32 5
  %15 = load i64* %14, align 8
  %16 = load %struct.network_t** %net_addr, align 8
  %17 = getelementptr inbounds %struct.network_t* %16, i32 0, i32 7
  %18 = load i64* %17, align 8
  %19 = sub nsw i64 %15, %18
  %20 = getelementptr inbounds %struct.arc* %12, i64 %19
  store %struct.arc* %20, %struct.arc** %new_arc, align 8
  store i64 0, i64* %susp, align 8
  %21 = load %struct.arc** %new_arc, align 8
  store %struct.arc* %21, %struct.arc** %arc, align 8
  br label %bb12

bb2:                                              ; preds = %bb12
  %22 = load %struct.arc** %arc, align 8
  %23 = getelementptr inbounds %struct.arc* %22, i32 0, i32 3
  %24 = load i32* %23, align 8
  %25 = icmp eq i32 %24, 1
  br i1 %25, label %bb3, label %bb4

bb3:                                              ; preds = %bb2
  %26 = load %struct.arc** %arc, align 8
  %27 = getelementptr inbounds %struct.arc* %26, i32 0, i32 0
  %28 = load i64* %27, align 8
  %29 = load %struct.arc** %arc, align 8
  %30 = getelementptr inbounds %struct.arc* %29, i32 0, i32 1
  %31 = load %struct.node** %30, align 8
  %32 = getelementptr inbounds %struct.node* %31, i32 0, i32 0
  %33 = load i64* %32, align 8
  %34 = sub nsw i64 %28, %33
  %35 = load %struct.arc** %arc, align 8
  %36 = getelementptr inbounds %struct.arc* %35, i32 0, i32 2
  %37 = load %struct.node** %36, align 8
  %38 = getelementptr inbounds %struct.node* %37, i32 0, i32 0
  %39 = load i64* %38, align 8
  %40 = add nsw i64 %34, %39
  store i64 %40, i64* %red_cost, align 8
  br label %bb8

bb4:                                              ; preds = %bb2
  store i64 -2, i64* %red_cost, align 8
  %41 = load %struct.arc** %arc, align 8
  %42 = getelementptr inbounds %struct.arc* %41, i32 0, i32 3
  %43 = load i32* %42, align 8
  %44 = icmp eq i32 %43, 0
  br i1 %44, label %bb5, label %bb8

bb5:                                              ; preds = %bb4
  %45 = load %struct.arc** %arc, align 8
  %46 = getelementptr inbounds %struct.arc* %45, i32 0, i32 1
  %47 = load %struct.node** %46, align 8
  %48 = getelementptr inbounds %struct.node* %47, i32 0, i32 6
  %49 = load %struct.arc** %48, align 8
  %50 = load %struct.arc** %arc, align 8
  %51 = icmp eq %struct.arc* %49, %50
  br i1 %51, label %bb6, label %bb7

bb6:                                              ; preds = %bb5
  %52 = load %struct.arc** %arc, align 8
  %53 = getelementptr inbounds %struct.arc* %52, i32 0, i32 1
  %54 = load %struct.node** %53, align 8
  %55 = getelementptr inbounds %struct.node* %54, i32 0, i32 6
  %56 = load %struct.arc** %new_arc, align 8
  store %struct.arc* %56, %struct.arc** %55, align 8
  br label %bb8

bb7:                                              ; preds = %bb5
  %57 = load %struct.arc** %arc, align 8
  %58 = getelementptr inbounds %struct.arc* %57, i32 0, i32 2
  %59 = load %struct.node** %58, align 8
  %60 = getelementptr inbounds %struct.node* %59, i32 0, i32 6
  %61 = load %struct.arc** %new_arc, align 8
  store %struct.arc* %61, %struct.arc** %60, align 8
  br label %bb8

bb8:                                              ; preds = %bb7, %bb6, %bb4, %bb3
  %62 = load i64* %red_cost, align 8
  %63 = load i64* %threshold_addr, align 8
  %64 = icmp sgt i64 %62, %63
  br i1 %64, label %bb9, label %bb10

bb9:                                              ; preds = %bb8
  %65 = load i64* %susp, align 8
  %66 = add nsw i64 %65, 1
  store i64 %66, i64* %susp, align 8
  br label %bb11

bb10:                                             ; preds = %bb8
  %67 = load %struct.arc** %new_arc, align 8
  %68 = load %struct.arc** %arc, align 8
  %69 = bitcast %struct.arc* %67 to i8*
  %70 = bitcast %struct.arc* %68 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %69, i8* %70, i64 64, i32 8, i1 false)
  %71 = load %struct.arc** %new_arc, align 8
  %72 = getelementptr inbounds %struct.arc* %71, i64 1
  store %struct.arc* %72, %struct.arc** %new_arc, align 8
  br label %bb11

bb11:                                             ; preds = %bb10, %bb9
  %73 = load %struct.arc** %arc, align 8
  %74 = getelementptr inbounds %struct.arc* %73, i64 1
  store %struct.arc* %74, %struct.arc** %arc, align 8
  br label %bb12

bb12:                                             ; preds = %bb11, %bb1
  %75 = load i8** %stop, align 8
  %76 = bitcast i8* %75 to %struct.arc*
  %77 = load %struct.arc** %arc, align 8
  %78 = icmp ult %struct.arc* %77, %76
  br i1 %78, label %bb2, label %bb13

bb13:                                             ; preds = %bb12, %bb
  %79 = load i64* %susp, align 8
  %80 = icmp ne i64 %79, 0
  br i1 %80, label %bb14, label %bb15

bb14:                                             ; preds = %bb13
  %81 = load %struct.network_t** %net_addr, align 8
  %82 = getelementptr inbounds %struct.network_t* %81, i32 0, i32 5
  %83 = load i64* %82, align 8
  %84 = load i64* %susp, align 8
  %85 = sub nsw i64 %83, %84
  %86 = load %struct.network_t** %net_addr, align 8
  %87 = getelementptr inbounds %struct.network_t* %86, i32 0, i32 5
  store i64 %85, i64* %87, align 8
  %88 = load %struct.network_t** %net_addr, align 8
  %89 = getelementptr inbounds %struct.network_t* %88, i32 0, i32 7
  %90 = load i64* %89, align 8
  %91 = load i64* %susp, align 8
  %92 = sub nsw i64 %90, %91
  %93 = load %struct.network_t** %net_addr, align 8
  %94 = getelementptr inbounds %struct.network_t* %93, i32 0, i32 7
  store i64 %92, i64* %94, align 8
  %95 = load %struct.network_t** %net_addr, align 8
  %96 = getelementptr inbounds %struct.network_t* %95, i32 0, i32 24
  %97 = load %struct.arc** %96, align 8
  %98 = load i64* %susp, align 8
  %99 = sub nsw i64 0, %98
  %100 = getelementptr inbounds %struct.arc* %97, i64 %99
  %101 = load %struct.network_t** %net_addr, align 8
  %102 = getelementptr inbounds %struct.network_t* %101, i32 0, i32 24
  store %struct.arc* %100, %struct.arc** %102, align 8
  %103 = load %struct.network_t** %net_addr, align 8
  %104 = getelementptr inbounds %struct.network_t* %103, i32 0, i32 8
  %105 = load i64* %104, align 8
  %106 = load i64* %susp, align 8
  %107 = add nsw i64 %105, %106
  %108 = load %struct.network_t** %net_addr, align 8
  %109 = getelementptr inbounds %struct.network_t* %108, i32 0, i32 8
  store i64 %107, i64* %109, align 8
  %110 = load %struct.network_t** %net_addr, align 8
  call void @refresh_neighbour_lists(%struct.network_t* %110) nounwind
  br label %bb15

bb15:                                             ; preds = %bb14, %bb13
  %111 = load i64* %susp, align 8
  store i64 %111, i64* %0, align 8
  %112 = load i64* %0, align 8
  store i64 %112, i64* %retval, align 8
  br label %return

return:                                           ; preds = %bb15
  %retval16 = load i64* %retval
  ret i64 %retval16
}

declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture, i64, i32, i1) nounwind

define i64 @global_opt() nounwind {
entry:
  %retval = alloca i64
  %0 = alloca i64
  %new_arcs = alloca i64
  %residual_nb_it = alloca i64
  %"alloca point" = bitcast i32 0 to i32
  store i64 -1, i64* %new_arcs, align 8
  store i64 5, i64* %residual_nb_it, align 8
  br label %bb9

bb:                                               ; preds = %bb9
  %1 = load i64* getelementptr inbounds (%struct.network_t* @net, i64 0, i32 5), align 8
  %2 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([34 x i8]* @.str3, i64 0, i64 0), i64 %1) nounwind
  %3 = call i64 @primal_net_simplex(%struct.network_t* @net) nounwind
  %4 = load i64* getelementptr inbounds (%struct.network_t* @net, i64 0, i32 27), align 8
  %5 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([34 x i8]* @.str14, i64 0, i64 0), i64 %4) nounwind
  %6 = call double @flow_cost(%struct.network_t* @net) nounwind
  %7 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([36 x i8]* @.str25, i64 0, i64 0), double %6) nounwind
  %8 = load i64* %residual_nb_it, align 8
  %9 = icmp eq i64 %8, 0
  br i1 %9, label %bb10, label %bb1

bb1:                                              ; preds = %bb
  %10 = load i64* getelementptr inbounds (%struct.network_t* @net, i64 0, i32 7), align 8
  %11 = icmp ne i64 %10, 0
  br i1 %11, label %bb2, label %bb4

bb2:                                              ; preds = %bb1
  %12 = call i64 @suspend_impl(%struct.network_t* @net, i64 -1, i64 0) nounwind
  store i64 %12, i64* %new_arcs, align 8
  %13 = load i64* %new_arcs, align 8
  %14 = icmp ne i64 %13, 0
  br i1 %14, label %bb3, label %bb4

bb3:                                              ; preds = %bb2
  %15 = load i64* %new_arcs, align 8
  %16 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([34 x i8]* @.str36, i64 0, i64 0), i64 %15) nounwind
  br label %bb4

bb4:                                              ; preds = %bb3, %bb2, %bb1
  %17 = call i64 @price_out_impl(%struct.network_t* @net) nounwind
  store i64 %17, i64* %new_arcs, align 8
  %18 = load i64* %new_arcs, align 8
  %19 = icmp ne i64 %18, 0
  br i1 %19, label %bb5, label %bb6

bb5:                                              ; preds = %bb4
  %20 = load i64* %new_arcs, align 8
  %21 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([34 x i8]* @.str4, i64 0, i64 0), i64 %20) nounwind
  br label %bb6

bb6:                                              ; preds = %bb5, %bb4
  %22 = load i64* %new_arcs, align 8
  %23 = icmp slt i64 %22, 0
  br i1 %23, label %bb7, label %bb8

bb7:                                              ; preds = %bb6
  %24 = call i32 @puts(i8* getelementptr inbounds ([28 x i8]* @.str5, i64 0, i64 0)) nounwind
  call void @exit(i32 -1) noreturn nounwind
  unreachable

bb8:                                              ; preds = %bb6
  %25 = load i64* %residual_nb_it, align 8
  %26 = sub nsw i64 %25, 1
  store i64 %26, i64* %residual_nb_it, align 8
  br label %bb9

bb9:                                              ; preds = %bb8, %entry
  %27 = load i64* %new_arcs, align 8
  %28 = icmp ne i64 %27, 0
  br i1 %28, label %bb, label %bb10

bb10:                                             ; preds = %bb9, %bb
  %29 = load i64* getelementptr inbounds (%struct.network_t* @net, i64 0, i32 29), align 8
  %30 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([34 x i8]* @.str6, i64 0, i64 0), i64 %29) nounwind
  store i64 0, i64* %0, align 8
  %31 = load i64* %0, align 8
  store i64 %31, i64* %retval, align 8
  br label %return

return:                                           ; preds = %bb10
  %retval11 = load i64* %retval
  ret i64 %retval11
}

declare i32 @puts(i8*)

declare void @exit(i32) noreturn nounwind

define i32 @main(i32 %argc, i8** %argv) nounwind {
entry:
  %argc_addr = alloca i32, align 4
  %argv_addr = alloca i8**, align 8
  %retval = alloca i32
  %0 = alloca i32
  %"alloca point" = bitcast i32 0 to i32
  store i32 %argc, i32* %argc_addr
  store i8** %argv, i8*** %argv_addr
  %1 = load i32* %argc_addr, align 4
  %2 = icmp sle i32 %1, 1
  br i1 %2, label %bb, label %bb1

bb:                                               ; preds = %entry
  store i32 -1, i32* %0, align 4
  br label %bb6

bb1:                                              ; preds = %entry
  %3 = call i32 @puts(i8* getelementptr inbounds ([31 x i8]* @.str7, i64 0, i64 0)) nounwind
  %4 = call i32 @puts(i8* getelementptr inbounds ([51 x i8]* @.str8, i64 0, i64 0)) nounwind
  %5 = call i32 @puts(i8* getelementptr inbounds ([45 x i8]* @.str9, i64 0, i64 0)) nounwind
  %6 = call i32 @puts(i8* getelementptr inbounds ([39 x i8]* @.str10, i64 0, i64 0)) nounwind
  %7 = call i32 @putchar(i32 10) nounwind
  call void @llvm.memset.p0i8.i64(i8* getelementptr inbounds (%struct.network_t* @net, i64 0, i32 0, i64 0), i8 0, i64 624, i32 1, i1 false)
  store i64 10000000, i64* getelementptr inbounds (%struct.network_t* @net, i64 0, i32 18), align 8
  %8 = load i8*** %argv_addr, align 8
  %9 = getelementptr inbounds i8** %8, i64 1
  %10 = load i8** %9, align 1
  %11 = call i8* @strcpy(i8* noalias getelementptr inbounds (%struct.network_t* @net, i64 0, i32 0, i64 0), i8* noalias %10) nounwind
  %12 = call i64 @read_min(%struct.network_t* @net) nounwind
  %13 = icmp ne i64 %12, 0
  br i1 %13, label %bb2, label %bb3

bb2:                                              ; preds = %bb1
  %14 = call i32 @puts(i8* getelementptr inbounds ([17 x i8]* @.str11, i64 0, i64 0)) nounwind
  %15 = call i64 @getfree(%struct.network_t* @net) nounwind
  store i32 -1, i32* %0, align 4
  br label %bb6

bb3:                                              ; preds = %bb1
  %16 = load i64* getelementptr inbounds (%struct.network_t* @net, i64 0, i32 3), align 8
  %17 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([34 x i8]* @.str12, i64 0, i64 0), i64 %16) nounwind
  %18 = call i64 @primal_start_artificial(%struct.network_t* @net) nounwind
  %19 = call i64 @global_opt() nounwind
  %20 = call i32 @puts(i8* getelementptr inbounds ([5 x i8]* @.str13, i64 0, i64 0)) nounwind
  %21 = call i64 @write_circulations(i8* getelementptr inbounds ([8 x i8]* @.str147, i64 0, i64 0), %struct.network_t* @net) nounwind
  %22 = icmp ne i64 %21, 0
  br i1 %22, label %bb4, label %bb5

bb4:                                              ; preds = %bb3
  %23 = call i64 @getfree(%struct.network_t* @net) nounwind
  store i32 -1, i32* %0, align 4
  br label %bb6

bb5:                                              ; preds = %bb3
  %24 = call i64 @getfree(%struct.network_t* @net) nounwind
  store i32 0, i32* %0, align 4
  br label %bb6

bb6:                                              ; preds = %bb5, %bb4, %bb2, %bb
  %25 = load i32* %0, align 4
  store i32 %25, i32* %retval, align 4
  br label %return

return:                                           ; preds = %bb6
  %retval7 = load i32* %retval
  ret i32 %retval7
}

declare i32 @putchar(i32)

declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) nounwind

declare i8* @strcpy(i8* noalias, i8* noalias) nounwind

define void @refresh_neighbour_lists(%struct.network_t* %net) nounwind {
entry:
  %net_addr = alloca %struct.network_t*, align 8
  %node = alloca %struct.node*
  %arc = alloca %struct.arc*
  %stop = alloca i8*
  %"alloca point" = bitcast i32 0 to i32
  store %struct.network_t* %net, %struct.network_t** %net_addr
  %0 = load %struct.network_t** %net_addr, align 8
  %1 = getelementptr inbounds %struct.network_t* %0, i32 0, i32 21
  %2 = load %struct.node** %1, align 8
  store %struct.node* %2, %struct.node** %node, align 8
  %3 = load %struct.network_t** %net_addr, align 8
  %4 = getelementptr inbounds %struct.network_t* %3, i32 0, i32 22
  %5 = load %struct.node** %4, align 8
  %6 = bitcast %struct.node* %5 to i8*
  store i8* %6, i8** %stop, align 8
  br label %bb1

bb:                                               ; preds = %bb1
  %7 = load %struct.node** %node, align 8
  %8 = getelementptr inbounds %struct.node* %7, i32 0, i32 8
  store %struct.arc* null, %struct.arc** %8, align 8
  %9 = load %struct.node** %node, align 8
  %10 = getelementptr inbounds %struct.node* %9, i32 0, i32 7
  store %struct.arc* null, %struct.arc** %10, align 8
  %11 = load %struct.node** %node, align 8
  %12 = getelementptr inbounds %struct.node* %11, i64 1
  store %struct.node* %12, %struct.node** %node, align 8
  br label %bb1

bb1:                                              ; preds = %bb, %entry
  %13 = load i8** %stop, align 8
  %14 = bitcast i8* %13 to %struct.node*
  %15 = load %struct.node** %node, align 8
  %16 = icmp ult %struct.node* %15, %14
  br i1 %16, label %bb, label %bb2

bb2:                                              ; preds = %bb1
  %17 = load %struct.network_t** %net_addr, align 8
  %18 = getelementptr inbounds %struct.network_t* %17, i32 0, i32 23
  %19 = load %struct.arc** %18, align 8
  store %struct.arc* %19, %struct.arc** %arc, align 8
  %20 = load %struct.network_t** %net_addr, align 8
  %21 = getelementptr inbounds %struct.network_t* %20, i32 0, i32 24
  %22 = load %struct.arc** %21, align 8
  %23 = bitcast %struct.arc* %22 to i8*
  store i8* %23, i8** %stop, align 8
  br label %bb4

bb3:                                              ; preds = %bb4
  %24 = load %struct.arc** %arc, align 8
  %25 = getelementptr inbounds %struct.arc* %24, i32 0, i32 1
  %26 = load %struct.node** %25, align 8
  %27 = getelementptr inbounds %struct.node* %26, i32 0, i32 7
  %28 = load %struct.arc** %27, align 8
  %29 = load %struct.arc** %arc, align 8
  %30 = getelementptr inbounds %struct.arc* %29, i32 0, i32 4
  store %struct.arc* %28, %struct.arc** %30, align 8
  %31 = load %struct.arc** %arc, align 8
  %32 = getelementptr inbounds %struct.arc* %31, i32 0, i32 1
  %33 = load %struct.node** %32, align 8
  %34 = getelementptr inbounds %struct.node* %33, i32 0, i32 7
  %35 = load %struct.arc** %arc, align 8
  store %struct.arc* %35, %struct.arc** %34, align 8
  %36 = load %struct.arc** %arc, align 8
  %37 = getelementptr inbounds %struct.arc* %36, i32 0, i32 2
  %38 = load %struct.node** %37, align 8
  %39 = getelementptr inbounds %struct.node* %38, i32 0, i32 8
  %40 = load %struct.arc** %39, align 8
  %41 = load %struct.arc** %arc, align 8
  %42 = getelementptr inbounds %struct.arc* %41, i32 0, i32 5
  store %struct.arc* %40, %struct.arc** %42, align 8
  %43 = load %struct.arc** %arc, align 8
  %44 = getelementptr inbounds %struct.arc* %43, i32 0, i32 2
  %45 = load %struct.node** %44, align 8
  %46 = getelementptr inbounds %struct.node* %45, i32 0, i32 8
  %47 = load %struct.arc** %arc, align 8
  store %struct.arc* %47, %struct.arc** %46, align 8
  %48 = load %struct.arc** %arc, align 8
  %49 = getelementptr inbounds %struct.arc* %48, i64 1
  store %struct.arc* %49, %struct.arc** %arc, align 8
  br label %bb4

bb4:                                              ; preds = %bb3, %bb2
  %50 = load i8** %stop, align 8
  %51 = bitcast i8* %50 to %struct.arc*
  %52 = load %struct.arc** %arc, align 8
  %53 = icmp ult %struct.arc* %52, %51
  br i1 %53, label %bb3, label %bb5

bb5:                                              ; preds = %bb4
  br label %return

return:                                           ; preds = %bb5
  ret void
}

define i64 @refresh_potential(%struct.network_t* %net) nounwind {
entry:
  %net_addr = alloca %struct.network_t*, align 8
  %retval = alloca i64
  %0 = alloca i64
  %node = alloca %struct.node*
  %tmp = alloca %struct.node*
  %root = alloca %struct.node*
  %checksum = alloca i64
  %"alloca point" = bitcast i32 0 to i32
  store %struct.network_t* %net, %struct.network_t** %net_addr
  %1 = load %struct.network_t** %net_addr, align 8
  %2 = getelementptr inbounds %struct.network_t* %1, i32 0, i32 21
  %3 = load %struct.node** %2, align 8
  store %struct.node* %3, %struct.node** %root, align 8
  store i64 0, i64* %checksum, align 8
  %4 = load %struct.node** %root, align 8
  %5 = getelementptr inbounds %struct.node* %4, i32 0, i32 0
  store i64 -100000000, i64* %5, align 8
  %6 = load %struct.node** %root, align 8
  %7 = getelementptr inbounds %struct.node* %6, i32 0, i32 2
  %8 = load %struct.node** %7, align 8
  store %struct.node* %8, %struct.node** %node, align 8
  %9 = load %struct.node** %node, align 8
  store %struct.node* %9, %struct.node** %tmp, align 8
  br label %bb11

bb:                                               ; preds = %bb11
  br label %bb5

bb1:                                              ; preds = %bb5
  %10 = load %struct.node** %node, align 8
  %11 = getelementptr inbounds %struct.node* %10, i32 0, i32 1
  %12 = load i32* %11, align 8
  %13 = icmp eq i32 %12, 1
  br i1 %13, label %bb2, label %bb3

bb2:                                              ; preds = %bb1
  %14 = load %struct.node** %node, align 8
  %15 = getelementptr inbounds %struct.node* %14, i32 0, i32 6
  %16 = load %struct.arc** %15, align 8
  %17 = getelementptr inbounds %struct.arc* %16, i32 0, i32 0
  %18 = load i64* %17, align 8
  %19 = load %struct.node** %node, align 8
  %20 = getelementptr inbounds %struct.node* %19, i32 0, i32 3
  %21 = load %struct.node** %20, align 8
  %22 = getelementptr inbounds %struct.node* %21, i32 0, i32 0
  %23 = load i64* %22, align 8
  %24 = add nsw i64 %18, %23
  %25 = load %struct.node** %node, align 8
  %26 = getelementptr inbounds %struct.node* %25, i32 0, i32 0
  store i64 %24, i64* %26, align 8
  br label %bb4

bb3:                                              ; preds = %bb1
  %27 = load %struct.node** %node, align 8
  %28 = getelementptr inbounds %struct.node* %27, i32 0, i32 3
  %29 = load %struct.node** %28, align 8
  %30 = getelementptr inbounds %struct.node* %29, i32 0, i32 0
  %31 = load i64* %30, align 8
  %32 = load %struct.node** %node, align 8
  %33 = getelementptr inbounds %struct.node* %32, i32 0, i32 6
  %34 = load %struct.arc** %33, align 8
  %35 = getelementptr inbounds %struct.arc* %34, i32 0, i32 0
  %36 = load i64* %35, align 8
  %37 = sub nsw i64 %31, %36
  %38 = load %struct.node** %node, align 8
  %39 = getelementptr inbounds %struct.node* %38, i32 0, i32 0
  store i64 %37, i64* %39, align 8
  %40 = load i64* %checksum, align 8
  %41 = add nsw i64 %40, 1
  store i64 %41, i64* %checksum, align 8
  br label %bb4

bb4:                                              ; preds = %bb3, %bb2
  %42 = load %struct.node** %node, align 8
  store %struct.node* %42, %struct.node** %tmp, align 8
  %43 = load %struct.node** %node, align 8
  %44 = getelementptr inbounds %struct.node* %43, i32 0, i32 2
  %45 = load %struct.node** %44, align 8
  store %struct.node* %45, %struct.node** %node, align 8
  br label %bb5

bb5:                                              ; preds = %bb4, %bb
  %46 = load %struct.node** %node, align 8
  %47 = icmp ne %struct.node* %46, null
  br i1 %47, label %bb1, label %bb6

bb6:                                              ; preds = %bb5
  %48 = load %struct.node** %tmp, align 8
  store %struct.node* %48, %struct.node** %node, align 8
  br label %bb10

bb7:                                              ; preds = %bb10
  %49 = load %struct.node** %node, align 8
  %50 = getelementptr inbounds %struct.node* %49, i32 0, i32 4
  %51 = load %struct.node** %50, align 8
  store %struct.node* %51, %struct.node** %tmp, align 8
  %52 = load %struct.node** %tmp, align 8
  %53 = icmp ne %struct.node* %52, null
  br i1 %53, label %bb8, label %bb9

bb8:                                              ; preds = %bb7
  %54 = load %struct.node** %tmp, align 8
  store %struct.node* %54, %struct.node** %node, align 8
  br label %bb11

bb9:                                              ; preds = %bb7
  %55 = load %struct.node** %node, align 8
  %56 = getelementptr inbounds %struct.node* %55, i32 0, i32 3
  %57 = load %struct.node** %56, align 8
  store %struct.node* %57, %struct.node** %node, align 8
  br label %bb10

bb10:                                             ; preds = %bb9, %bb6
  %58 = load %struct.node** %node, align 8
  %59 = getelementptr inbounds %struct.node* %58, i32 0, i32 3
  %60 = load %struct.node** %59, align 8
  %61 = icmp ne %struct.node* %60, null
  br i1 %61, label %bb7, label %bb11

bb11:                                             ; preds = %bb10, %bb8, %entry
  %62 = load %struct.node** %node, align 8
  %63 = load %struct.node** %root, align 8
  %64 = icmp ne %struct.node* %62, %63
  br i1 %64, label %bb, label %bb12

bb12:                                             ; preds = %bb11
  %65 = load i64* %checksum, align 8
  store i64 %65, i64* %0, align 8
  %66 = load i64* %0, align 8
  store i64 %66, i64* %retval, align 8
  br label %return

return:                                           ; preds = %bb12
  %retval13 = load i64* %retval
  ret i64 %retval13
}

define double @flow_cost(%struct.network_t* %net) nounwind {
entry:
  %net_addr = alloca %struct.network_t*, align 8
  %retval = alloca double
  %0 = alloca double
  %arc = alloca %struct.arc*
  %node = alloca %struct.node*
  %stop = alloca i8*
  %fleet = alloca i64
  %operational_cost = alloca i64
  %"alloca point" = bitcast i32 0 to i32
  store %struct.network_t* %net, %struct.network_t** %net_addr
  store i64 0, i64* %fleet, align 8
  store i64 0, i64* %operational_cost, align 8
  %1 = load %struct.network_t** %net_addr, align 8
  %2 = getelementptr inbounds %struct.network_t* %1, i32 0, i32 24
  %3 = load %struct.arc** %2, align 8
  %4 = bitcast %struct.arc* %3 to i8*
  store i8* %4, i8** %stop, align 8
  %5 = load %struct.network_t** %net_addr, align 8
  %6 = getelementptr inbounds %struct.network_t* %5, i32 0, i32 23
  %7 = load %struct.arc** %6, align 8
  store %struct.arc* %7, %struct.arc** %arc, align 8
  br label %bb4

bb:                                               ; preds = %bb4
  %8 = load %struct.arc** %arc, align 8
  %9 = getelementptr inbounds %struct.arc* %8, i32 0, i32 3
  %10 = load i32* %9, align 8
  %11 = icmp eq i32 %10, 2
  br i1 %11, label %bb1, label %bb2

bb1:                                              ; preds = %bb
  %12 = load %struct.arc** %arc, align 8
  %13 = getelementptr inbounds %struct.arc* %12, i32 0, i32 6
  store i64 1, i64* %13, align 8
  br label %bb3

bb2:                                              ; preds = %bb
  %14 = load %struct.arc** %arc, align 8
  %15 = getelementptr inbounds %struct.arc* %14, i32 0, i32 6
  store i64 0, i64* %15, align 8
  br label %bb3

bb3:                                              ; preds = %bb2, %bb1
  %16 = load %struct.arc** %arc, align 8
  %17 = getelementptr inbounds %struct.arc* %16, i64 1
  store %struct.arc* %17, %struct.arc** %arc, align 8
  br label %bb4

bb4:                                              ; preds = %bb3, %entry
  %18 = load i8** %stop, align 8
  %19 = bitcast i8* %18 to %struct.arc*
  %20 = load %struct.arc** %arc, align 8
  %21 = icmp ne %struct.arc* %20, %19
  br i1 %21, label %bb, label %bb5

bb5:                                              ; preds = %bb4
  %22 = load %struct.network_t** %net_addr, align 8
  %23 = getelementptr inbounds %struct.network_t* %22, i32 0, i32 22
  %24 = load %struct.node** %23, align 8
  %25 = bitcast %struct.node* %24 to i8*
  store i8* %25, i8** %stop, align 8
  %26 = load %struct.network_t** %net_addr, align 8
  %27 = getelementptr inbounds %struct.network_t* %26, i32 0, i32 21
  %28 = load %struct.node** %27, align 8
  store %struct.node* %28, %struct.node** %node, align 8
  %29 = load %struct.node** %node, align 8
  %30 = getelementptr inbounds %struct.node* %29, i64 1
  store %struct.node* %30, %struct.node** %node, align 8
  br label %bb7

bb6:                                              ; preds = %bb7
  %31 = load %struct.node** %node, align 8
  %32 = getelementptr inbounds %struct.node* %31, i32 0, i32 6
  %33 = load %struct.arc** %32, align 8
  %34 = load %struct.node** %node, align 8
  %35 = getelementptr inbounds %struct.node* %34, i32 0, i32 10
  %36 = load i64* %35, align 8
  %37 = getelementptr inbounds %struct.arc* %33, i32 0, i32 6
  store i64 %36, i64* %37, align 8
  %38 = load %struct.node** %node, align 8
  %39 = getelementptr inbounds %struct.node* %38, i64 1
  store %struct.node* %39, %struct.node** %node, align 8
  br label %bb7

bb7:                                              ; preds = %bb6, %bb5
  %40 = load i8** %stop, align 8
  %41 = bitcast i8* %40 to %struct.node*
  %42 = load %struct.node** %node, align 8
  %43 = icmp ne %struct.node* %42, %41
  br i1 %43, label %bb6, label %bb8

bb8:                                              ; preds = %bb7
  %44 = load %struct.network_t** %net_addr, align 8
  %45 = getelementptr inbounds %struct.network_t* %44, i32 0, i32 24
  %46 = load %struct.arc** %45, align 8
  %47 = bitcast %struct.arc* %46 to i8*
  store i8* %47, i8** %stop, align 8
  %48 = load %struct.network_t** %net_addr, align 8
  %49 = getelementptr inbounds %struct.network_t* %48, i32 0, i32 23
  %50 = load %struct.arc** %49, align 8
  store %struct.arc* %50, %struct.arc** %arc, align 8
  br label %bb16

bb9:                                              ; preds = %bb16
  %51 = load %struct.arc** %arc, align 8
  %52 = getelementptr inbounds %struct.arc* %51, i32 0, i32 6
  %53 = load i64* %52, align 8
  %54 = icmp ne i64 %53, 0
  br i1 %54, label %bb10, label %bb15

bb10:                                             ; preds = %bb9
  %55 = load %struct.arc** %arc, align 8
  %56 = getelementptr inbounds %struct.arc* %55, i32 0, i32 1
  %57 = load %struct.node** %56, align 8
  %58 = getelementptr inbounds %struct.node* %57, i32 0, i32 12
  %59 = load i32* %58, align 8
  %60 = icmp sge i32 %59, 0
  br i1 %60, label %bb12, label %bb11

bb11:                                             ; preds = %bb10
  %61 = load %struct.arc** %arc, align 8
  %62 = getelementptr inbounds %struct.arc* %61, i32 0, i32 2
  %63 = load %struct.node** %62, align 8
  %64 = getelementptr inbounds %struct.node* %63, i32 0, i32 12
  %65 = load i32* %64, align 8
  %66 = icmp sle i32 %65, 0
  br i1 %66, label %bb12, label %bb15

bb12:                                             ; preds = %bb11, %bb10
  %67 = load %struct.arc** %arc, align 8
  %68 = getelementptr inbounds %struct.arc* %67, i32 0, i32 1
  %69 = load %struct.node** %68, align 8
  %70 = getelementptr inbounds %struct.node* %69, i32 0, i32 12
  %71 = load i32* %70, align 8
  %72 = icmp eq i32 %71, 0
  br i1 %72, label %bb13, label %bb14

bb13:                                             ; preds = %bb12
  %73 = load %struct.arc** %arc, align 8
  %74 = getelementptr inbounds %struct.arc* %73, i32 0, i32 0
  %75 = load i64* %74, align 8
  %76 = load %struct.network_t** %net_addr, align 8
  %77 = getelementptr inbounds %struct.network_t* %76, i32 0, i32 18
  %78 = load i64* %77, align 8
  %79 = sub nsw i64 %75, %78
  %80 = load i64* %operational_cost, align 8
  %81 = add nsw i64 %79, %80
  store i64 %81, i64* %operational_cost, align 8
  %82 = load i64* %fleet, align 8
  %83 = add nsw i64 %82, 1
  store i64 %83, i64* %fleet, align 8
  br label %bb15

bb14:                                             ; preds = %bb12
  %84 = load %struct.arc** %arc, align 8
  %85 = getelementptr inbounds %struct.arc* %84, i32 0, i32 0
  %86 = load i64* %85, align 8
  %87 = load i64* %operational_cost, align 8
  %88 = add nsw i64 %86, %87
  store i64 %88, i64* %operational_cost, align 8
  br label %bb15

bb15:                                             ; preds = %bb14, %bb13, %bb11, %bb9
  %89 = load %struct.arc** %arc, align 8
  %90 = getelementptr inbounds %struct.arc* %89, i64 1
  store %struct.arc* %90, %struct.arc** %arc, align 8
  br label %bb16

bb16:                                             ; preds = %bb15, %bb8
  %91 = load i8** %stop, align 8
  %92 = bitcast i8* %91 to %struct.arc*
  %93 = load %struct.arc** %arc, align 8
  %94 = icmp ne %struct.arc* %93, %92
  br i1 %94, label %bb9, label %bb17

bb17:                                             ; preds = %bb16
  %95 = load i64* %fleet, align 8
  %96 = sitofp i64 %95 to double
  %97 = load %struct.network_t** %net_addr, align 8
  %98 = getelementptr inbounds %struct.network_t* %97, i32 0, i32 18
  %99 = load i64* %98, align 8
  %100 = sitofp i64 %99 to double
  %101 = fmul double %96, %100
  %102 = load i64* %operational_cost, align 8
  %103 = sitofp i64 %102 to double
  %104 = fadd double %101, %103
  store double %104, double* %0, align 8
  %105 = load double* %0, align 8
  store double %105, double* %retval, align 8
  br label %return

return:                                           ; preds = %bb17
  %retval18 = load double* %retval
  ret double %retval18
}

define double @flow_org_cost(%struct.network_t* %net) nounwind {
entry:
  %net_addr = alloca %struct.network_t*, align 8
  %retval = alloca double
  %0 = alloca double
  %arc = alloca %struct.arc*
  %node = alloca %struct.node*
  %stop = alloca i8*
  %fleet = alloca i64
  %operational_cost = alloca i64
  %"alloca point" = bitcast i32 0 to i32
  store %struct.network_t* %net, %struct.network_t** %net_addr
  store i64 0, i64* %fleet, align 8
  store i64 0, i64* %operational_cost, align 8
  %1 = load %struct.network_t** %net_addr, align 8
  %2 = getelementptr inbounds %struct.network_t* %1, i32 0, i32 24
  %3 = load %struct.arc** %2, align 8
  %4 = bitcast %struct.arc* %3 to i8*
  store i8* %4, i8** %stop, align 8
  %5 = load %struct.network_t** %net_addr, align 8
  %6 = getelementptr inbounds %struct.network_t* %5, i32 0, i32 23
  %7 = load %struct.arc** %6, align 8
  store %struct.arc* %7, %struct.arc** %arc, align 8
  br label %bb4

bb:                                               ; preds = %bb4
  %8 = load %struct.arc** %arc, align 8
  %9 = getelementptr inbounds %struct.arc* %8, i32 0, i32 3
  %10 = load i32* %9, align 8
  %11 = icmp eq i32 %10, 2
  br i1 %11, label %bb1, label %bb2

bb1:                                              ; preds = %bb
  %12 = load %struct.arc** %arc, align 8
  %13 = getelementptr inbounds %struct.arc* %12, i32 0, i32 6
  store i64 1, i64* %13, align 8
  br label %bb3

bb2:                                              ; preds = %bb
  %14 = load %struct.arc** %arc, align 8
  %15 = getelementptr inbounds %struct.arc* %14, i32 0, i32 6
  store i64 0, i64* %15, align 8
  br label %bb3

bb3:                                              ; preds = %bb2, %bb1
  %16 = load %struct.arc** %arc, align 8
  %17 = getelementptr inbounds %struct.arc* %16, i64 1
  store %struct.arc* %17, %struct.arc** %arc, align 8
  br label %bb4

bb4:                                              ; preds = %bb3, %entry
  %18 = load i8** %stop, align 8
  %19 = bitcast i8* %18 to %struct.arc*
  %20 = load %struct.arc** %arc, align 8
  %21 = icmp ne %struct.arc* %20, %19
  br i1 %21, label %bb, label %bb5

bb5:                                              ; preds = %bb4
  %22 = load %struct.network_t** %net_addr, align 8
  %23 = getelementptr inbounds %struct.network_t* %22, i32 0, i32 22
  %24 = load %struct.node** %23, align 8
  %25 = bitcast %struct.node* %24 to i8*
  store i8* %25, i8** %stop, align 8
  %26 = load %struct.network_t** %net_addr, align 8
  %27 = getelementptr inbounds %struct.network_t* %26, i32 0, i32 21
  %28 = load %struct.node** %27, align 8
  store %struct.node* %28, %struct.node** %node, align 8
  %29 = load %struct.node** %node, align 8
  %30 = getelementptr inbounds %struct.node* %29, i64 1
  store %struct.node* %30, %struct.node** %node, align 8
  br label %bb7

bb6:                                              ; preds = %bb7
  %31 = load %struct.node** %node, align 8
  %32 = getelementptr inbounds %struct.node* %31, i32 0, i32 6
  %33 = load %struct.arc** %32, align 8
  %34 = load %struct.node** %node, align 8
  %35 = getelementptr inbounds %struct.node* %34, i32 0, i32 10
  %36 = load i64* %35, align 8
  %37 = getelementptr inbounds %struct.arc* %33, i32 0, i32 6
  store i64 %36, i64* %37, align 8
  %38 = load %struct.node** %node, align 8
  %39 = getelementptr inbounds %struct.node* %38, i64 1
  store %struct.node* %39, %struct.node** %node, align 8
  br label %bb7

bb7:                                              ; preds = %bb6, %bb5
  %40 = load i8** %stop, align 8
  %41 = bitcast i8* %40 to %struct.node*
  %42 = load %struct.node** %node, align 8
  %43 = icmp ne %struct.node* %42, %41
  br i1 %43, label %bb6, label %bb8

bb8:                                              ; preds = %bb7
  %44 = load %struct.network_t** %net_addr, align 8
  %45 = getelementptr inbounds %struct.network_t* %44, i32 0, i32 24
  %46 = load %struct.arc** %45, align 8
  %47 = bitcast %struct.arc* %46 to i8*
  store i8* %47, i8** %stop, align 8
  %48 = load %struct.network_t** %net_addr, align 8
  %49 = getelementptr inbounds %struct.network_t* %48, i32 0, i32 23
  %50 = load %struct.arc** %49, align 8
  store %struct.arc* %50, %struct.arc** %arc, align 8
  br label %bb16

bb9:                                              ; preds = %bb16
  %51 = load %struct.arc** %arc, align 8
  %52 = getelementptr inbounds %struct.arc* %51, i32 0, i32 6
  %53 = load i64* %52, align 8
  %54 = icmp ne i64 %53, 0
  br i1 %54, label %bb10, label %bb15

bb10:                                             ; preds = %bb9
  %55 = load %struct.arc** %arc, align 8
  %56 = getelementptr inbounds %struct.arc* %55, i32 0, i32 1
  %57 = load %struct.node** %56, align 8
  %58 = getelementptr inbounds %struct.node* %57, i32 0, i32 12
  %59 = load i32* %58, align 8
  %60 = icmp sge i32 %59, 0
  br i1 %60, label %bb12, label %bb11

bb11:                                             ; preds = %bb10
  %61 = load %struct.arc** %arc, align 8
  %62 = getelementptr inbounds %struct.arc* %61, i32 0, i32 2
  %63 = load %struct.node** %62, align 8
  %64 = getelementptr inbounds %struct.node* %63, i32 0, i32 12
  %65 = load i32* %64, align 8
  %66 = icmp sle i32 %65, 0
  br i1 %66, label %bb12, label %bb15

bb12:                                             ; preds = %bb11, %bb10
  %67 = load %struct.arc** %arc, align 8
  %68 = getelementptr inbounds %struct.arc* %67, i32 0, i32 1
  %69 = load %struct.node** %68, align 8
  %70 = getelementptr inbounds %struct.node* %69, i32 0, i32 12
  %71 = load i32* %70, align 8
  %72 = icmp eq i32 %71, 0
  br i1 %72, label %bb13, label %bb14

bb13:                                             ; preds = %bb12
  %73 = load %struct.arc** %arc, align 8
  %74 = getelementptr inbounds %struct.arc* %73, i32 0, i32 7
  %75 = load i64* %74, align 8
  %76 = load %struct.network_t** %net_addr, align 8
  %77 = getelementptr inbounds %struct.network_t* %76, i32 0, i32 18
  %78 = load i64* %77, align 8
  %79 = sub nsw i64 %75, %78
  %80 = load i64* %operational_cost, align 8
  %81 = add nsw i64 %79, %80
  store i64 %81, i64* %operational_cost, align 8
  %82 = load i64* %fleet, align 8
  %83 = add nsw i64 %82, 1
  store i64 %83, i64* %fleet, align 8
  br label %bb15

bb14:                                             ; preds = %bb12
  %84 = load %struct.arc** %arc, align 8
  %85 = getelementptr inbounds %struct.arc* %84, i32 0, i32 7
  %86 = load i64* %85, align 8
  %87 = load i64* %operational_cost, align 8
  %88 = add nsw i64 %86, %87
  store i64 %88, i64* %operational_cost, align 8
  br label %bb15

bb15:                                             ; preds = %bb14, %bb13, %bb11, %bb9
  %89 = load %struct.arc** %arc, align 8
  %90 = getelementptr inbounds %struct.arc* %89, i64 1
  store %struct.arc* %90, %struct.arc** %arc, align 8
  br label %bb16

bb16:                                             ; preds = %bb15, %bb8
  %91 = load i8** %stop, align 8
  %92 = bitcast i8* %91 to %struct.arc*
  %93 = load %struct.arc** %arc, align 8
  %94 = icmp ne %struct.arc* %93, %92
  br i1 %94, label %bb9, label %bb17

bb17:                                             ; preds = %bb16
  %95 = load i64* %fleet, align 8
  %96 = sitofp i64 %95 to double
  %97 = load %struct.network_t** %net_addr, align 8
  %98 = getelementptr inbounds %struct.network_t* %97, i32 0, i32 18
  %99 = load i64* %98, align 8
  %100 = sitofp i64 %99 to double
  %101 = fmul double %96, %100
  %102 = load i64* %operational_cost, align 8
  %103 = sitofp i64 %102 to double
  %104 = fadd double %101, %103
  store double %104, double* %0, align 8
  %105 = load double* %0, align 8
  store double %105, double* %retval, align 8
  br label %return

return:                                           ; preds = %bb17
  %retval18 = load double* %retval
  ret double %retval18
}

define i64 @primal_feasible(%struct.network_t* %net) nounwind {
entry:
  %net_addr = alloca %struct.network_t*, align 8
  %retval = alloca i64
  %0 = alloca i64
  %stop = alloca i8*
  %node = alloca %struct.node*
  %dummy = alloca %struct.arc*
  %stop_dummy = alloca %struct.arc*
  %arc = alloca %struct.arc*
  %flow = alloca i64
  %"alloca point" = bitcast i32 0 to i32
  store %struct.network_t* %net, %struct.network_t** %net_addr
  %1 = load %struct.network_t** %net_addr, align 8
  %2 = getelementptr inbounds %struct.network_t* %1, i32 0, i32 25
  %3 = load %struct.arc** %2, align 8
  store %struct.arc* %3, %struct.arc** %dummy, align 8
  %4 = load %struct.network_t** %net_addr, align 8
  %5 = getelementptr inbounds %struct.network_t* %4, i32 0, i32 26
  %6 = load %struct.arc** %5, align 8
  store %struct.arc* %6, %struct.arc** %stop_dummy, align 8
  %7 = load %struct.network_t** %net_addr, align 8
  %8 = getelementptr inbounds %struct.network_t* %7, i32 0, i32 21
  %9 = load %struct.node** %8, align 8
  store %struct.node* %9, %struct.node** %node, align 8
  %10 = load %struct.network_t** %net_addr, align 8
  %11 = getelementptr inbounds %struct.network_t* %10, i32 0, i32 22
  %12 = load %struct.node** %11, align 8
  %13 = bitcast %struct.node* %12 to i8*
  store i8* %13, i8** %stop, align 8
  %14 = load %struct.node** %node, align 8
  %15 = getelementptr inbounds %struct.node* %14, i64 1
  store %struct.node* %15, %struct.node** %node, align 8
  br label %bb10

bb:                                               ; preds = %bb10
  %16 = load %struct.node** %node, align 8
  %17 = getelementptr inbounds %struct.node* %16, i32 0, i32 6
  %18 = load %struct.arc** %17, align 8
  store %struct.arc* %18, %struct.arc** %arc, align 8
  %19 = load %struct.node** %node, align 8
  %20 = getelementptr inbounds %struct.node* %19, i32 0, i32 10
  %21 = load i64* %20, align 8
  store i64 %21, i64* %flow, align 8
  %22 = load %struct.arc** %arc, align 8
  %23 = load %struct.arc** %dummy, align 8
  %24 = icmp ult %struct.arc* %22, %23
  br i1 %24, label %bb6, label %bb1

bb1:                                              ; preds = %bb
  %25 = load %struct.arc** %arc, align 8
  %26 = load %struct.arc** %stop_dummy, align 8
  %27 = icmp uge %struct.arc* %25, %26
  br i1 %27, label %bb6, label %bb2

bb2:                                              ; preds = %bb1
  %28 = load i64* %flow, align 8
  %neg = sub i64 0, %28
  %abscond = icmp sge i64 %28, 0
  %abs = select i1 %abscond, i64 %28, i64 %neg
  %29 = load %struct.network_t** %net_addr, align 8
  %30 = getelementptr inbounds %struct.network_t* %29, i32 0, i32 16
  %31 = load i64* %30, align 8
  %32 = icmp sgt i64 %abs, %31
  br i1 %32, label %bb4, label %bb5

bb4:                                              ; preds = %bb2
  %33 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([25 x i8]* @.str15, i64 0, i64 0)) nounwind
  %34 = load %struct.node** %node, align 8
  %35 = getelementptr inbounds %struct.node* %34, i32 0, i32 12
  %36 = load i32* %35, align 8
  %37 = load i64* %flow, align 8
  %38 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([49 x i8]* @.str116, i64 0, i64 0), i32 %36, i64 %37) nounwind
  br label %bb5

bb5:                                              ; preds = %bb4, %bb2
  br label %bb9

bb6:                                              ; preds = %bb1, %bb
  %39 = load %struct.network_t** %net_addr, align 8
  %40 = getelementptr inbounds %struct.network_t* %39, i32 0, i32 16
  %41 = load i64* %40, align 8
  %42 = sub nsw i64 0, %41
  %43 = load i64* %flow, align 8
  %44 = icmp sgt i64 %42, %43
  br i1 %44, label %bb8, label %bb7

bb7:                                              ; preds = %bb6
  %45 = load i64* %flow, align 8
  %46 = sub nsw i64 %45, 1
  %47 = load %struct.network_t** %net_addr, align 8
  %48 = getelementptr inbounds %struct.network_t* %47, i32 0, i32 16
  %49 = load i64* %48, align 8
  %50 = icmp sgt i64 %46, %49
  br i1 %50, label %bb8, label %bb9

bb8:                                              ; preds = %bb7, %bb6
  %51 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([25 x i8]* @.str15, i64 0, i64 0)) nounwind
  %52 = load i64* %flow, align 8
  %53 = call i32 (i8*, ...)* @printf(i8* noalias getelementptr inbounds ([31 x i8]* @.str217, i64 0, i64 0), i64 %52) nounwind
  %54 = load %struct.network_t** %net_addr, align 8
  %55 = getelementptr inbounds %struct.network_t* %54, i32 0, i32 13
  store i64 0, i64* %55, align 8
  store i64 1, i64* %0, align 8
  br label %bb12

bb9:                                              ; preds = %bb7, %bb5
  %56 = load %struct.node** %node, align 8
  %57 = getelementptr inbounds %struct.node* %56, i64 1
  store %struct.node* %57, %struct.node** %node, align 8
  br label %bb10

bb10:                                             ; preds = %bb9, %entry
  %58 = load i8** %stop, align 8
  %59 = bitcast i8* %58 to %struct.node*
  %60 = load %struct.node** %node, align 8
  %61 = icmp ult %struct.node* %60, %59
  br i1 %61, label %bb, label %bb11

bb11:                                             ; preds = %bb10
  %62 = load %struct.network_t** %net_addr, align 8
  %63 = getelementptr inbounds %struct.network_t* %62, i32 0, i32 13
  store i64 1, i64* %63, align 8
  store i64 0, i64* %0, align 8
  br label %bb12

bb12:                                             ; preds = %bb11, %bb8
  %64 = load i64* %0, align 8
  store i64 %64, i64* %retval, align 8
  br label %return

return:                                           ; preds = %bb12
  %retval13 = load i64* %retval
  ret i64 %retval13
}

define i64 @dual_feasible(%struct.network_t* %net) nounwind {
entry:
  %net_addr = alloca %struct.network_t*, align 8
  %retval = alloca i64
  %0 = alloca i64
  %arc = alloca %struct.arc*
  %stop = alloca %struct.arc*
  %red_cost = alloca i64
  %"alloca point" = bitcast i32 0 to i32
  store %struct.network_t* %net, %struct.network_t** %net_addr
  %1 = load %struct.network_t** %net_addr, align 8
  %2 = getelementptr inbounds %struct.network_t* %1, i32 0, i32 24
  %3 = load %struct.arc** %2, align 8
  store %struct.arc* %3, %struct.arc** %stop, align 8
  %4 = load %struct.network_t** %net_addr, align 8
  %5 = getelementptr inbounds %struct.network_t* %4, i32 0, i32 23
  %6 = load %struct.arc** %5, align 8
  store %struct.arc* %6, %struct.arc** %arc, align 8
  br label %bb5

bb:                                               ; preds = %bb5
  %7 = load %struct.arc** %arc, align 8
  %8 = getelementptr inbounds %struct.arc* %7, i32 0, i32 0
  %9 = load i64* %8, align 8
  %10 = load %struct.arc** %arc, align 8
  %11 = getelementptr inbounds %struct.arc* %10, i32 0, i32 1
  %12 = load %struct.node** %11, align 8
  %13 = getelementptr inbounds %struct.node* %12, i32 0, i32 0
  %14 = load i64* %13, align 8
  %15 = sub nsw i64 %9, %14
  %16 = load %struct.arc** %arc, align 8
  %17 = getelementptr inbounds %struct.arc* %16, i32 0, i32 2
  %18 = load %struct.node** %17, align 8
  %19 = getelementptr inbounds %struct.node* %18, i32 0, i32 0
  %20 = load i64* %19, align 8
  %21 = add nsw i64 %15, %20
  store i64 %21, i64* %red_cost, align 8
  %22 = load %struct.arc** %arc, align 8
  %23 = getelementptr inbounds %struct.arc* %22, i32 0, i32 3
  %24 = load i32* %23, align 8
  switch i32 %24, label %bb4 [
    i32 0, label %bb1
    i32 1, label %bb1
    i32 2, label %bb3
  ]

bb1:                                              ; preds = %bb, %bb
  %25 = load %struct.network_t** %net_addr, align 8
  %26 = getelementptr inbounds %struct.network_t* %25, i32 0, i32 16
  %27 = load i64* %26, align 8
  %28 = sub nsw i64 0, %27
  %29 = load i64* %red_cost, align 8
  %30 = icmp sgt i64 %28, %29
  br i1 %30, label %DUAL_INFEAS, label %bb2

bb2:                                              ; preds = %bb1
  br label %bb4

bb3:                                              ; preds = %bb
  %31 = load %struct.network_t** %net_addr, align 8
  %32 = getelementptr inbounds %struct.network_t* %31, i32 0, i32 16
  %33 = load i64* %32, align 8
  %34 = load i64* %red_cost, align 8
  %35 = icmp slt i64 %33, %34
  br i1 %35, label %DUAL_INFEAS, label %bb4

bb4:                                              ; preds = %bb3, %bb2, %bb
  %36 = load %struct.arc** %arc, align 8
  %37 = getelementptr inbounds %struct.arc* %36, i64 1
  store %struct.arc* %37, %struct.arc** %arc, align 8
  br label %bb5

bb5:                                              ; preds = %bb4, %entry
  %38 = load %struct.arc** %arc, align 8
  %39 = load %struct.arc** %stop, align 8
  %40 = icmp ult %struct.arc* %38, %39
  br i1 %40, label %bb, label %bb6

bb6:                                              ; preds = %bb5
  store i64 0, i64* %0, align 8
  br label %bb7

DUAL_INFEAS:                                      ; preds = %bb3, %bb1
  %41 = load %struct.FILE** @stderr, align 8
  %42 = bitcast %struct.FILE* %41 to i8*
  %43 = call i64 @fwrite(i8* getelementptr inbounds ([23 x i8]* @.str318, i64 0, i64 0), i64 1, i64 22, i8* %42) nounwind
  %44 = load %struct.FILE** @stderr, align 8
  %45 = bitcast %struct.FILE* %44 to i8*
  %46 = call i64 @fwrite(i8* getelementptr inbounds ([23 x i8]* @.str419, i64 0, i64 0), i64 1, i64 22, i8* %45) nounwind
  store i64 1, i64* %0, align 8
  br label %bb7

bb7:                                              ; preds = %DUAL_INFEAS, %bb6
  %47 = load i64* %0, align 8
  store i64 %47, i64* %retval, align 8
  br label %return

return:                                           ; preds = %bb7
  %retval8 = load i64* %retval
  ret i64 %retval8
}

declare i64 @fwrite(i8*, i64, i64, i8*)

define i64 @getfree(%struct.network_t* %net) nounwind {
entry:
  %net_addr = alloca %struct.network_t*, align 8
  %retval = alloca i64
  %0 = alloca i64
  %"alloca point" = bitcast i32 0 to i32
  store %struct.network_t* %net, %struct.network_t** %net_addr
  %1 = load %struct.network_t** %net_addr, align 8
  %2 = getelementptr inbounds %struct.network_t* %1, i32 0, i32 21
  %3 = load %struct.node** %2, align 8
  %4 = icmp ne %struct.node* %3, null
  br i1 %4, label %bb, label %bb1

bb:                                               ; preds = %entry
  %5 = load %struct.network_t** %net_addr, align 8
  %6 = getelementptr inbounds %struct.network_t* %5, i32 0, i32 21
  %7 = load %struct.node** %6, align 8
  %8 = bitcast %struct.node* %7 to i8*
  call void @free(i8* %8) nounwind
  br label %bb1

bb1:                                              ; preds = %bb, %entry
  %9 = load %struct.network_t** %net_addr, align 8
  %10 = getelementptr inbounds %struct.network_t* %9, i32 0, i32 23
  %11 = load %struct.arc** %10, align 8
  %12 = icmp ne %struct.arc* %11, null
  br i1 %12, label %bb2, label %bb3

bb2:                                              ; preds = %bb1
  %13 = load %struct.network_t** %net_addr, align 8
  %14 = getelementptr inbounds %struct.network_t* %13, i32 0, i32 23
  %15 = load %struct.arc** %14, align 8
  %16 = bitcast %struct.arc* %15 to i8*
  call void @free(i8* %16) nounwind
  br label %bb3

bb3:                                              ; preds = %bb2, %bb1
  %17 = load %struct.network_t** %net_addr, align 8
  %18 = getelementptr inbounds %struct.network_t* %17, i32 0, i32 25
  %19 = load %struct.arc** %18, align 8
  %20 = icmp ne %struct.arc* %19, null
  br i1 %20, label %bb4, label %bb5

bb4:                                              ; preds = %bb3
  %21 = load %struct.network_t** %net_addr, align 8
  %22 = getelementptr inbounds %struct.network_t* %21, i32 0, i32 25
  %23 = load %struct.arc** %22, align 8
  %24 = bitcast %struct.arc* %23 to i8*
  call void @free(i8* %24) nounwind
  br label %bb5

bb5:                                              ; preds = %bb4, %bb3
  %25 = load %struct.network_t** %net_addr, align 8
  %26 = getelementptr inbounds %struct.network_t* %25, i32 0, i32 22
  store %struct.node* null, %struct.node** %26, align 8
  %27 = load %struct.network_t** %net_addr, align 8
  %28 = getelementptr inbounds %struct.network_t* %27, i32 0, i32 22
  %29 = load %struct.node** %28, align 8
  %30 = load %struct.network_t** %net_addr, align 8
  %31 = getelementptr inbounds %struct.network_t* %30, i32 0, i32 21
  store %struct.node* %29, %struct.node** %31, align 8
  %32 = load %struct.network_t** %net_addr, align 8
  %33 = getelementptr inbounds %struct.network_t* %32, i32 0, i32 24
  store %struct.arc* null, %struct.arc** %33, align 8
  %34 = load %struct.network_t** %net_addr, align 8
  %35 = getelementptr inbounds %struct.network_t* %34, i32 0, i32 24
  %36 = load %struct.arc** %35, align 8
  %37 = load %struct.network_t** %net_addr, align 8
  %38 = getelementptr inbounds %struct.network_t* %37, i32 0, i32 23
  store %struct.arc* %36, %struct.arc** %38, align 8
  %39 = load %struct.network_t** %net_addr, align 8
  %40 = getelementptr inbounds %struct.network_t* %39, i32 0, i32 26
  store %struct.arc* null, %struct.arc** %40, align 8
  %41 = load %struct.network_t** %net_addr, align 8
  %42 = getelementptr inbounds %struct.network_t* %41, i32 0, i32 26
  %43 = load %struct.arc** %42, align 8
  %44 = load %struct.network_t** %net_addr, align 8
  %45 = getelementptr inbounds %struct.network_t* %44, i32 0, i32 25
  store %struct.arc* %43, %struct.arc** %45, align 8
  store i64 0, i64* %0, align 8
  %46 = load i64* %0, align 8
  store i64 %46, i64* %retval, align 8
  br label %return

return:                                           ; preds = %bb5
  %retval6 = load i64* %retval
  ret i64 %retval6
}

declare void @free(i8*) nounwind

define i64 @write_circulations(i8* %outfile, %struct.network_t* %net) nounwind {
entry:
  %outfile_addr = alloca i8*, align 8
  %net_addr = alloca %struct.network_t*, align 8
  %retval = alloca i64
  %0 = alloca i64
  %out = alloca %struct.FILE*
  %block = alloca %struct.arc*
  %arc = alloca %struct.arc*
  %arc2 = alloca %struct.arc*
  %first_impl = alloca %struct.arc*
  %"alloca point" = bitcast i32 0 to i32
  store i8* %outfile, i8** %outfile_addr
  store %struct.network_t* %net, %struct.network_t** %net_addr
  store %struct.FILE* null, %struct.FILE** %out, align 8
  %1 = load %struct.network_t** %net_addr, align 8
  %2 = getelementptr inbounds %struct.network_t* %1, i32 0, i32 24
  %3 = load %struct.arc** %2, align 8
  %4 = load %struct.network_t** %net_addr, align 8
  %5 = getelementptr inbounds %struct.network_t* %4, i32 0, i32 7
  %6 = load i64* %5, align 8
  %7 = sub nsw i64 0, %6
  %8 = getelementptr inbounds %struct.arc* %3, i64 %7
  store %struct.arc* %8, %struct.arc** %first_impl, align 8
  %9 = load i8** %outfile_addr, align 8
  %10 = call %struct.FILE* @fopen(i8* noalias %9, i8* noalias getelementptr inbounds ([2 x i8]* @.str23, i64 0, i64 0)) nounwind
  store %struct.FILE* %10, %struct.FILE** %out, align 8
  %11 = load %struct.FILE** %out, align 8
  %12 = icmp eq %struct.FILE* %11, null
  br i1 %12, label %bb, label %bb1

bb:                                               ; preds = %entry
  store i64 -1, i64* %0, align 8
  br label %bb19

bb1:                                              ; preds = %entry
  %13 = load %struct.network_t** %net_addr, align 8
  call void @refresh_neighbour_lists(%struct.network_t* %13) nounwind
  %14 = load %struct.network_t** %net_addr, align 8
  %15 = getelementptr inbounds %struct.network_t* %14, i32 0, i32 21
  %16 = load %struct.node** %15, align 8
  %17 = load %struct.network_t** %net_addr, align 8
  %18 = getelementptr inbounds %struct.network_t* %17, i32 0, i32 2
  %19 = load i64* %18, align 8
  %20 = getelementptr inbounds %struct.node* %16, i64 %19
  %21 = getelementptr inbounds %struct.node* %20, i32 0, i32 7
  %22 = load %struct.arc** %21, align 8
  store %struct.arc* %22, %struct.arc** %block, align 8
  br label %bb17

bb2:                                              ; preds = %bb17
  %23 = load %struct.arc** %block, align 8
  %24 = getelementptr inbounds %struct.arc* %23, i32 0, i32 6
  %25 = load i64* %24, align 8
  %26 = icmp ne i64 %25, 0
  br i1 %26, label %bb3, label %bb16

bb3:                                              ; preds = %bb2
  %27 = load %struct.FILE** %out, align 8
  %28 = bitcast %struct.FILE* %27 to i8*
  %29 = call i64 @fwrite(i8* getelementptr inbounds ([4 x i8]* @.str124, i64 0, i64 0), i64 1, i64 3, i8* %28) nounwind
  %30 = load %struct.arc** %block, align 8
  store %struct.arc* %30, %struct.arc** %arc, align 8
  br label %bb15

bb4:                                              ; preds = %bb15
  %31 = load %struct.arc** %arc, align 8
  %32 = load %struct.arc** %first_impl, align 8
  %33 = icmp uge %struct.arc* %31, %32
  br i1 %33, label %bb5, label %bb6

bb5:                                              ; preds = %bb4
  %34 = load %struct.FILE** %out, align 8
  %35 = bitcast %struct.FILE* %34 to i8*
  %36 = call i64 @fwrite(i8* getelementptr inbounds ([5 x i8]* @.str225, i64 0, i64 0), i64 1, i64 4, i8* %35) nounwind
  br label %bb6

bb6:                                              ; preds = %bb5, %bb4
  %37 = load %struct.arc** %arc, align 8
  %38 = getelementptr inbounds %struct.arc* %37, i32 0, i32 2
  %39 = load %struct.node** %38, align 8
  %40 = getelementptr inbounds %struct.node* %39, i32 0, i32 12
  %41 = load i32* %40, align 8
  %42 = sub nsw i32 0, %41
  %43 = load %struct.FILE** %out, align 8
  %44 = call i32 (%struct.FILE*, i8*, ...)* @fprintf(%struct.FILE* noalias %43, i8* noalias getelementptr inbounds ([4 x i8]* @.str326, i64 0, i64 0), i32 %42) nounwind
  %45 = load %struct.arc** %arc, align 8
  %46 = getelementptr inbounds %struct.arc* %45, i32 0, i32 2
  %47 = load %struct.node** %46, align 8
  %48 = load %struct.network_t** %net_addr, align 8
  %49 = getelementptr inbounds %struct.network_t* %48, i32 0, i32 3
  %50 = load i64* %49, align 8
  %51 = getelementptr inbounds %struct.node* %47, i64 %50
  %52 = getelementptr inbounds %struct.node* %51, i32 0, i32 7
  %53 = load %struct.arc** %52, align 8
  store %struct.arc* %53, %struct.arc** %arc2, align 8
  br label %bb9

bb7:                                              ; preds = %bb9
  %54 = load %struct.arc** %arc2, align 8
  %55 = getelementptr inbounds %struct.arc* %54, i32 0, i32 6
  %56 = load i64* %55, align 8
  %57 = icmp ne i64 %56, 0
  br i1 %57, label %bb10, label %bb8

bb8:                                              ; preds = %bb7
  %58 = load %struct.arc** %arc2, align 8
  %59 = getelementptr inbounds %struct.arc* %58, i32 0, i32 4
  %60 = load %struct.arc** %59, align 8
  store %struct.arc* %60, %struct.arc** %arc2, align 8
  br label %bb9

bb9:                                              ; preds = %bb8, %bb6
  %61 = load %struct.arc** %arc2, align 8
  %62 = icmp ne %struct.arc* %61, null
  br i1 %62, label %bb7, label %bb10

bb10:                                             ; preds = %bb9, %bb7
  %63 = load %struct.arc** %arc2, align 8
  %64 = icmp eq %struct.arc* %63, null
  br i1 %64, label %bb11, label %bb12

bb11:                                             ; preds = %bb10
  %65 = load %struct.FILE** %out, align 8
  %66 = call i32 @fclose(%struct.FILE* %65) nounwind
  store i64 -1, i64* %0, align 8
  br label %bb19

bb12:                                             ; preds = %bb10
  %67 = load %struct.arc** %arc2, align 8
  %68 = getelementptr inbounds %struct.arc* %67, i32 0, i32 2
  %69 = load %struct.node** %68, align 8
  %70 = getelementptr inbounds %struct.node* %69, i32 0, i32 12
  %71 = load i32* %70, align 8
  %72 = icmp ne i32 %71, 0
  br i1 %72, label %bb13, label %bb14

bb13:                                             ; preds = %bb12
  %73 = load %struct.arc** %arc2, align 8
  store %struct.arc* %73, %struct.arc** %arc, align 8
  br label %bb15

bb14:                                             ; preds = %bb12
  store %struct.arc* null, %struct.arc** %arc, align 8
  br label %bb15

bb15:                                             ; preds = %bb14, %bb13, %bb3
  %74 = load %struct.arc** %arc, align 8
  %75 = icmp ne %struct.arc* %74, null
  br i1 %75, label %bb4, label %bb16

bb16:                                             ; preds = %bb15, %bb2
  %76 = load %struct.arc** %block, align 8
  %77 = getelementptr inbounds %struct.arc* %76, i32 0, i32 4
  %78 = load %struct.arc** %77, align 8
  store %struct.arc* %78, %struct.arc** %block, align 8
  br label %bb17

bb17:                                             ; preds = %bb16, %bb1
  %79 = load %struct.arc** %block, align 8
  %80 = icmp ne %struct.arc* %79, null
  br i1 %80, label %bb2, label %bb18

bb18:                                             ; preds = %bb17
  %81 = load %struct.FILE** %out, align 8
  %82 = call i32 @fclose(%struct.FILE* %81) nounwind
  store i64 0, i64* %0, align 8
  br label %bb19

bb19:                                             ; preds = %bb18, %bb11, %bb
  %83 = load i64* %0, align 8
  store i64 %83, i64* %retval, align 8
  br label %return

return:                                           ; preds = %bb19
  %retval20 = load i64* %retval
  ret i64 %retval20
}

declare %struct.FILE* @fopen(i8* noalias, i8* noalias)

declare i32 @fprintf(%struct.FILE* noalias, i8* noalias, ...) nounwind

declare i32 @fclose(%struct.FILE*)

define i32 @bea_is_dual_infeasible(%struct.arc* %arc, i64 %red_cost) nounwind {
entry:
  %arc_addr = alloca %struct.arc*, align 8
  %red_cost_addr = alloca i64, align 8
  %retval = alloca i32
  %iftmp.0 = alloca i32
  %0 = alloca i32
  %"alloca point" = bitcast i32 0 to i32
  store %struct.arc* %arc, %struct.arc** %arc_addr
  store i64 %red_cost, i64* %red_cost_addr
  %1 = load i64* %red_cost_addr, align 8
  %2 = icmp sge i64 %1, 0
  br i1 %2, label %bb1, label %bb

bb:                                               ; preds = %entry
  %3 = load %struct.arc** %arc_addr, align 8
  %4 = getelementptr inbounds %struct.arc* %3, i32 0, i32 3
  %5 = load i32* %4, align 8
  %6 = icmp eq i32 %5, 1
  br i1 %6, label %bb3, label %bb1

bb1:                                              ; preds = %bb, %entry
  %7 = load i64* %red_cost_addr, align 8
  %8 = icmp sle i64 %7, 0
  br i1 %8, label %bb4, label %bb2

bb2:                                              ; preds = %bb1
  %9 = load %struct.arc** %arc_addr, align 8
  %10 = getelementptr inbounds %struct.arc* %9, i32 0, i32 3
  %11 = load i32* %10, align 8
  %12 = icmp eq i32 %11, 2
  br i1 %12, label %bb3, label %bb4

bb3:                                              ; preds = %bb2, %bb
  store i32 1, i32* %iftmp.0, align 4
  br label %bb5

bb4:                                              ; preds = %bb2, %bb1
  store i32 0, i32* %iftmp.0, align 4
  br label %bb5

bb5:                                              ; preds = %bb4, %bb3
  %13 = load i32* %iftmp.0, align 4
  store i32 %13, i32* %0, align 4
  %14 = load i32* %0, align 4
  store i32 %14, i32* %retval, align 4
  br label %return

return:                                           ; preds = %bb5
  %retval6 = load i32* %retval
  ret i32 %retval6
}

define void @sort_basket(i64 %min, i64 %max) nounwind {
entry:
  %min_addr = alloca i64, align 8
  %max_addr = alloca i64, align 8
  %l = alloca i64
  %r = alloca i64
  %cut = alloca i64
  %xchange = alloca %struct.BASKET*
  %"alloca point" = bitcast i32 0 to i32
  store i64 %min, i64* %min_addr
  store i64 %max, i64* %max_addr
  %0 = load i64* %min_addr, align 8
  store i64 %0, i64* %l, align 8
  %1 = load i64* %max_addr, align 8
  store i64 %1, i64* %r, align 8
  %2 = load i64* %l, align 8
  %3 = load i64* %r, align 8
  %4 = add nsw i64 %2, %3
  %5 = sdiv i64 %4, 2
  %6 = getelementptr inbounds [351 x %struct.BASKET*]* @perm, i64 0, i64 %5
  %7 = load %struct.BASKET** %6, align 8
  %8 = getelementptr inbounds %struct.BASKET* %7, i32 0, i32 2
  %9 = load i64* %8, align 8
  store i64 %9, i64* %cut, align 8
  br label %bb

bb:                                               ; preds = %bb10, %entry
  br label %bb2

bb1:                                              ; preds = %bb2
  %10 = load i64* %l, align 8
  %11 = add nsw i64 %10, 1
  store i64 %11, i64* %l, align 8
  br label %bb2

bb2:                                              ; preds = %bb1, %bb
  %12 = load i64* %l, align 8
  %13 = getelementptr inbounds [351 x %struct.BASKET*]* @perm, i64 0, i64 %12
  %14 = load %struct.BASKET** %13, align 8
  %15 = getelementptr inbounds %struct.BASKET* %14, i32 0, i32 2
  %16 = load i64* %15, align 8
  %17 = load i64* %cut, align 8
  %18 = icmp sgt i64 %16, %17
  br i1 %18, label %bb1, label %bb3

bb3:                                              ; preds = %bb2
  br label %bb5

bb4:                                              ; preds = %bb5
  %19 = load i64* %r, align 8
  %20 = sub nsw i64 %19, 1
  store i64 %20, i64* %r, align 8
  br label %bb5

bb5:                                              ; preds = %bb4, %bb3
  %21 = load i64* %r, align 8
  %22 = getelementptr inbounds [351 x %struct.BASKET*]* @perm, i64 0, i64 %21
  %23 = load %struct.BASKET** %22, align 8
  %24 = getelementptr inbounds %struct.BASKET* %23, i32 0, i32 2
  %25 = load i64* %24, align 8
  %26 = load i64* %cut, align 8
  %27 = icmp slt i64 %25, %26
  br i1 %27, label %bb4, label %bb6

bb6:                                              ; preds = %bb5
  %28 = load i64* %l, align 8
  %29 = load i64* %r, align 8
  %30 = icmp slt i64 %28, %29
  br i1 %30, label %bb7, label %bb8

bb7:                                              ; preds = %bb6
  %31 = load i64* %l, align 8
  %32 = getelementptr inbounds [351 x %struct.BASKET*]* @perm, i64 0, i64 %31
  %33 = load %struct.BASKET** %32, align 8
  store %struct.BASKET* %33, %struct.BASKET** %xchange, align 8
  %34 = load i64* %l, align 8
  %35 = load i64* %r, align 8
  %36 = getelementptr inbounds [351 x %struct.BASKET*]* @perm, i64 0, i64 %35
  %37 = load %struct.BASKET** %36, align 8
  %38 = getelementptr inbounds [351 x %struct.BASKET*]* @perm, i64 0, i64 %34
  store %struct.BASKET* %37, %struct.BASKET** %38, align 8
  %39 = load i64* %r, align 8
  %40 = getelementptr inbounds [351 x %struct.BASKET*]* @perm, i64 0, i64 %39
  %41 = load %struct.BASKET** %xchange, align 8
  store %struct.BASKET* %41, %struct.BASKET** %40, align 8
  br label %bb8

bb8:                                              ; preds = %bb7, %bb6
  %42 = load i64* %l, align 8
  %43 = load i64* %r, align 8
  %44 = icmp sle i64 %42, %43
  br i1 %44, label %bb9, label %bb10

bb9:                                              ; preds = %bb8
  %45 = load i64* %l, align 8
  %46 = add nsw i64 %45, 1
  store i64 %46, i64* %l, align 8
  %47 = load i64* %r, align 8
  %48 = sub nsw i64 %47, 1
  store i64 %48, i64* %r, align 8
  br label %bb10

bb10:                                             ; preds = %bb9, %bb8
  %49 = load i64* %l, align 8
  %50 = load i64* %r, align 8
  %51 = icmp sle i64 %49, %50
  br i1 %51, label %bb, label %bb11

bb11:                                             ; preds = %bb10
  %52 = load i64* %min_addr, align 8
  %53 = load i64* %r, align 8
  %54 = icmp slt i64 %52, %53
  br i1 %54, label %bb12, label %bb13

bb12:                                             ; preds = %bb11
  %55 = load i64* %min_addr, align 8
  %56 = load i64* %r, align 8
  call void @sort_basket(i64 %55, i64 %56) nounwind
  br label %bb13

bb13:                                             ; preds = %bb12, %bb11
  %57 = load i64* %l, align 8
  %58 = load i64* %max_addr, align 8
  %59 = icmp slt i64 %57, %58
  br i1 %59, label %bb14, label %bb16

bb14:                                             ; preds = %bb13
  %60 = load i64* %l, align 8
  %61 = icmp sle i64 %60, 50
  br i1 %61, label %bb15, label %bb16

bb15:                                             ; preds = %bb14
  %62 = load i64* %l, align 8
  %63 = load i64* %max_addr, align 8
  call void @sort_basket(i64 %62, i64 %63) nounwind
  br label %bb16

bb16:                                             ; preds = %bb15, %bb14, %bb13
  br label %return

return:                                           ; preds = %bb16
  ret void
}

define %struct.arc* @primal_bea_mpp(i64 %m, %struct.arc* %arcs, %struct.arc* %stop_arcs, i64* %red_cost_of_bea) nounwind {
entry:
  %m_addr = alloca i64, align 8
  %arcs_addr = alloca %struct.arc*, align 8
  %stop_arcs_addr = alloca %struct.arc*, align 8
  %red_cost_of_bea_addr = alloca i64*, align 8
  %retval = alloca %struct.arc*
  %0 = alloca %struct.arc*
  %i = alloca i64
  %next = alloca i64
  %old_group_pos = alloca i64
  %arc = alloca %struct.arc*
  %red_cost = alloca i64
  %"alloca point" = bitcast i32 0 to i32
  store i64 %m, i64* %m_addr
  store %struct.arc* %arcs, %struct.arc** %arcs_addr
  store %struct.arc* %stop_arcs, %struct.arc** %stop_arcs_addr
  store i64* %red_cost_of_bea, i64** %red_cost_of_bea_addr
  %1 = load i64* @initialize, align 8
  %2 = icmp ne i64 %1, 0
  br i1 %2, label %bb, label %bb4

bb:                                               ; preds = %entry
  store i64 1, i64* %i, align 8
  br label %bb2

bb1:                                              ; preds = %bb2
  %3 = load i64* %i, align 8
  %4 = load i64* %i, align 8
  %5 = getelementptr inbounds [351 x %struct.BASKET]* @basket, i64 0, i64 %4
  %6 = getelementptr inbounds [351 x %struct.BASKET*]* @perm, i64 0, i64 %3
  store %struct.BASKET* %5, %struct.BASKET** %6, align 8
  %7 = load i64* %i, align 8
  %8 = add nsw i64 %7, 1
  store i64 %8, i64* %i, align 8
  br label %bb2

bb2:                                              ; preds = %bb1, %bb
  %9 = load i64* %i, align 8
  %10 = icmp sle i64 %9, 350
  br i1 %10, label %bb1, label %bb3

bb3:                                              ; preds = %bb2
  %11 = load i64* %m_addr, align 8
  %12 = sub nsw i64 %11, 1
  %13 = sdiv i64 %12, 300
  %14 = add nsw i64 %13, 1
  store i64 %14, i64* @nr_group, align 8
  store i64 0, i64* @group_pos, align 8
  store i64 0, i64* @basket_size, align 8
  store i64 0, i64* @initialize, align 8
  br label %bb15

bb4:                                              ; preds = %entry
  store i64 2, i64* %i, align 8
  store i64 0, i64* %next, align 8
  br label %bb12

bb5:                                              ; preds = %bb13
  %15 = load i64* %i, align 8
  %16 = getelementptr inbounds [351 x %struct.BASKET*]* @perm, i64 0, i64 %15
  %17 = load %struct.BASKET** %16, align 8
  %18 = getelementptr inbounds %struct.BASKET* %17, i32 0, i32 0
  %19 = load %struct.arc** %18, align 8
  store %struct.arc* %19, %struct.arc** %arc, align 8
  %20 = load %struct.arc** %arc, align 8
  %21 = getelementptr inbounds %struct.arc* %20, i32 0, i32 0
  %22 = load i64* %21, align 8
  %23 = load %struct.arc** %arc, align 8
  %24 = getelementptr inbounds %struct.arc* %23, i32 0, i32 1
  %25 = load %struct.node** %24, align 8
  %26 = getelementptr inbounds %struct.node* %25, i32 0, i32 0
  %27 = load i64* %26, align 8
  %28 = sub nsw i64 %22, %27
  %29 = load %struct.arc** %arc, align 8
  %30 = getelementptr inbounds %struct.arc* %29, i32 0, i32 2
  %31 = load %struct.node** %30, align 8
  %32 = getelementptr inbounds %struct.node* %31, i32 0, i32 0
  %33 = load i64* %32, align 8
  %34 = add nsw i64 %28, %33
  store i64 %34, i64* %red_cost, align 8
  %35 = load i64* %red_cost, align 8
  %36 = icmp sge i64 %35, 0
  br i1 %36, label %bb7, label %bb6

bb6:                                              ; preds = %bb5
  %37 = load %struct.arc** %arc, align 8
  %38 = getelementptr inbounds %struct.arc* %37, i32 0, i32 3
  %39 = load i32* %38, align 8
  %40 = icmp eq i32 %39, 1
  br i1 %40, label %bb9, label %bb7

bb7:                                              ; preds = %bb6, %bb5
  %41 = load i64* %red_cost, align 8
  %42 = icmp sle i64 %41, 0
  br i1 %42, label %bb11, label %bb8

bb8:                                              ; preds = %bb7
  %43 = load %struct.arc** %arc, align 8
  %44 = getelementptr inbounds %struct.arc* %43, i32 0, i32 3
  %45 = load i32* %44, align 8
  %46 = icmp eq i32 %45, 2
  br i1 %46, label %bb9, label %bb11

bb9:                                              ; preds = %bb8, %bb6
  %47 = load i64* %next, align 8
  %48 = add nsw i64 %47, 1
  store i64 %48, i64* %next, align 8
  %49 = load i64* %next, align 8
  %50 = getelementptr inbounds [351 x %struct.BASKET*]* @perm, i64 0, i64 %49
  %51 = load %struct.BASKET** %50, align 8
  %52 = getelementptr inbounds %struct.BASKET* %51, i32 0, i32 0
  %53 = load %struct.arc** %arc, align 8
  store %struct.arc* %53, %struct.arc** %52, align 8
  %54 = load i64* %next, align 8
  %55 = getelementptr inbounds [351 x %struct.BASKET*]* @perm, i64 0, i64 %54
  %56 = load %struct.BASKET** %55, align 8
  %57 = getelementptr inbounds %struct.BASKET* %56, i32 0, i32 1
  %58 = load i64* %red_cost, align 8
  store i64 %58, i64* %57, align 8
  %59 = load i64* %next, align 8
  %60 = getelementptr inbounds [351 x %struct.BASKET*]* @perm, i64 0, i64 %59
  %61 = load %struct.BASKET** %60, align 8
  %62 = load i64* %red_cost, align 8
  %neg = sub i64 0, %62
  %abscond = icmp sge i64 %62, 0
  %abs = select i1 %abscond, i64 %62, i64 %neg
  %63 = getelementptr inbounds %struct.BASKET* %61, i32 0, i32 2
  store i64 %abs, i64* %63, align 8
  br label %bb11

bb11:                                             ; preds = %bb9, %bb8, %bb7
  %64 = load i64* %i, align 8
  %65 = add nsw i64 %64, 1
  store i64 %65, i64* %i, align 8
  br label %bb12

bb12:                                             ; preds = %bb11, %bb4
  %66 = load i64* %i, align 8
  %67 = icmp sgt i64 %66, 50
  br i1 %67, label %bb14, label %bb13

bb13:                                             ; preds = %bb12
  %68 = load i64* @basket_size, align 8
  %69 = load i64* %i, align 8
  %70 = icmp sle i64 %69, %68
  br i1 %70, label %bb5, label %bb14

bb14:                                             ; preds = %bb13, %bb12
  %71 = load i64* %next, align 8
  store i64 %71, i64* @basket_size, align 8
  br label %bb15

bb15:                                             ; preds = %bb14, %bb3
  %72 = load i64* @group_pos, align 8
  store i64 %72, i64* %old_group_pos, align 8
  br label %NEXT

NEXT:                                             ; preds = %bb28, %bb15
  %73 = load i64* @group_pos, align 8
  %74 = load %struct.arc** %arcs_addr, align 8
  %75 = getelementptr inbounds %struct.arc* %74, i64 %73
  store %struct.arc* %75, %struct.arc** %arc, align 8
  br label %bb24

bb16:                                             ; preds = %bb24
  %76 = load %struct.arc** %arc, align 8
  %77 = getelementptr inbounds %struct.arc* %76, i32 0, i32 3
  %78 = load i32* %77, align 8
  %79 = icmp sgt i32 %78, 0
  br i1 %79, label %bb17, label %bb23

bb17:                                             ; preds = %bb16
  %80 = load %struct.arc** %arc, align 8
  %81 = getelementptr inbounds %struct.arc* %80, i32 0, i32 0
  %82 = load i64* %81, align 8
  %83 = load %struct.arc** %arc, align 8
  %84 = getelementptr inbounds %struct.arc* %83, i32 0, i32 1
  %85 = load %struct.node** %84, align 8
  %86 = getelementptr inbounds %struct.node* %85, i32 0, i32 0
  %87 = load i64* %86, align 8
  %88 = sub nsw i64 %82, %87
  %89 = load %struct.arc** %arc, align 8
  %90 = getelementptr inbounds %struct.arc* %89, i32 0, i32 2
  %91 = load %struct.node** %90, align 8
  %92 = getelementptr inbounds %struct.node* %91, i32 0, i32 0
  %93 = load i64* %92, align 8
  %94 = add nsw i64 %88, %93
  store i64 %94, i64* %red_cost, align 8
  %95 = load %struct.arc** %arc, align 8
  %96 = load i64* %red_cost, align 8
  %97 = call i32 @bea_is_dual_infeasible(%struct.arc* %95, i64 %96) nounwind
  %98 = icmp ne i32 %97, 0
  br i1 %98, label %bb18, label %bb23

bb18:                                             ; preds = %bb17
  %99 = load i64* @basket_size, align 8
  %100 = add nsw i64 %99, 1
  store i64 %100, i64* @basket_size, align 8
  %101 = load i64* @basket_size, align 8
  %102 = getelementptr inbounds [351 x %struct.BASKET*]* @perm, i64 0, i64 %101
  %103 = load %struct.BASKET** %102, align 8
  %104 = getelementptr inbounds %struct.BASKET* %103, i32 0, i32 0
  %105 = load %struct.arc** %arc, align 8
  store %struct.arc* %105, %struct.arc** %104, align 8
  %106 = load i64* @basket_size, align 8
  %107 = getelementptr inbounds [351 x %struct.BASKET*]* @perm, i64 0, i64 %106
  %108 = load %struct.BASKET** %107, align 8
  %109 = getelementptr inbounds %struct.BASKET* %108, i32 0, i32 1
  %110 = load i64* %red_cost, align 8
  store i64 %110, i64* %109, align 8
  %111 = load i64* @basket_size, align 8
  %112 = getelementptr inbounds [351 x %struct.BASKET*]* @perm, i64 0, i64 %111
  %113 = load %struct.BASKET** %112, align 8
  %114 = load i64* %red_cost, align 8
  %neg19 = sub i64 0, %114
  %abscond20 = icmp sge i64 %114, 0
  %abs21 = select i1 %abscond20, i64 %114, i64 %neg19
  %115 = getelementptr inbounds %struct.BASKET* %113, i32 0, i32 2
  store i64 %abs21, i64* %115, align 8
  br label %bb23

bb23:                                             ; preds = %bb18, %bb17, %bb16
  %116 = load i64* @nr_group, align 8
  %117 = load %struct.arc** %arc, align 8
  %118 = getelementptr inbounds %struct.arc* %117, i64 %116
  store %struct.arc* %118, %struct.arc** %arc, align 8
  br label %bb24

bb24:                                             ; preds = %bb23, %NEXT
  %119 = load %struct.arc** %arc, align 8
  %120 = load %struct.arc** %stop_arcs_addr, align 8
  %121 = icmp ult %struct.arc* %119, %120
  br i1 %121, label %bb16, label %bb25

bb25:                                             ; preds = %bb24
  %122 = load i64* @group_pos, align 8
  %123 = add nsw i64 %122, 1
  store i64 %123, i64* @group_pos, align 8
  %124 = load i64* @group_pos, align 8
  %125 = load i64* @nr_group, align 8
  %126 = icmp eq i64 %124, %125
  br i1 %126, label %bb26, label %bb27

bb26:                                             ; preds = %bb25
  store i64 0, i64* @group_pos, align 8
  br label %bb27

bb27:                                             ; preds = %bb26, %bb25
  %127 = load i64* @basket_size, align 8
  %128 = icmp sle i64 %127, 49
  br i1 %128, label %bb28, label %bb29

bb28:                                             ; preds = %bb27
  %129 = load i64* @group_pos, align 8
  %130 = load i64* %old_group_pos, align 8
  %131 = icmp ne i64 %129, %130
  br i1 %131, label %NEXT, label %bb29

bb29:                                             ; preds = %bb28, %bb27
  %132 = load i64* @basket_size, align 8
  %133 = icmp eq i64 %132, 0
  br i1 %133, label %bb30, label %bb31

bb30:                                             ; preds = %bb29
  store i64 1, i64* @initialize, align 8
  %134 = load i64** %red_cost_of_bea_addr, align 8
  store i64 0, i64* %134, align 8
  store %struct.arc* null, %struct.arc** %0, align 8
  br label %bb32

bb31:                                             ; preds = %bb29
  %135 = load i64* @basket_size, align 8
  call void @sort_basket(i64 1, i64 %135) nounwind
  %136 = load %struct.BASKET** getelementptr inbounds ([351 x %struct.BASKET*]* @perm, i64 0, i64 1), align 8
  %137 = getelementptr inbounds %struct.BASKET* %136, i32 0, i32 1
  %138 = load i64* %137, align 8
  %139 = load i64** %red_cost_of_bea_addr, align 8
  store i64 %138, i64* %139, align 8
  %140 = load %struct.BASKET** getelementptr inbounds ([351 x %struct.BASKET*]* @perm, i64 0, i64 1), align 8
  %141 = getelementptr inbounds %struct.BASKET* %140, i32 0, i32 0
  %142 = load %struct.arc** %141, align 8
  store %struct.arc* %142, %struct.arc** %0, align 8
  br label %bb32

bb32:                                             ; preds = %bb31, %bb30
  %143 = load %struct.arc** %0, align 8
  store %struct.arc* %143, %struct.arc** %retval, align 8
  br label %return

return:                                           ; preds = %bb32
  %retval33 = load %struct.arc** %retval
  ret %struct.arc* %retval33
}

define %struct.node* @primal_iminus(i64* %delta, i64* %xchange, %struct.node* %iplus, %struct.node* %jplus, %struct.node** %w) nounwind {
entry:
  %delta_addr = alloca i64*, align 8
  %xchange_addr = alloca i64*, align 8
  %iplus_addr = alloca %struct.node*, align 8
  %jplus_addr = alloca %struct.node*, align 8
  %w_addr = alloca %struct.node**, align 8
  %retval = alloca %struct.node*
  %0 = alloca %struct.node*
  %iminus = alloca %struct.node*
  %"alloca point" = bitcast i32 0 to i32
  store i64* %delta, i64** %delta_addr
  store i64* %xchange, i64** %xchange_addr
  store %struct.node* %iplus, %struct.node** %iplus_addr
  store %struct.node* %jplus, %struct.node** %jplus_addr
  store %struct.node** %w, %struct.node*** %w_addr
  store %struct.node* null, %struct.node** %iminus, align 8
  br label %bb17

bb:                                               ; preds = %bb17
  %1 = load %struct.node** %iplus_addr, align 8
  %2 = getelementptr inbounds %struct.node* %1, i32 0, i32 11
  %3 = load i64* %2, align 8
  %4 = load %struct.node** %jplus_addr, align 8
  %5 = getelementptr inbounds %struct.node* %4, i32 0, i32 11
  %6 = load i64* %5, align 8
  %7 = icmp slt i64 %3, %6
  br i1 %7, label %bb1, label %bb9

bb1:                                              ; preds = %bb
  %8 = load %struct.node** %iplus_addr, align 8
  %9 = getelementptr inbounds %struct.node* %8, i32 0, i32 1
  %10 = load i32* %9, align 8
  %11 = icmp ne i32 %10, 0
  br i1 %11, label %bb2, label %bb5

bb2:                                              ; preds = %bb1
  %12 = load i64** %delta_addr, align 8
  %13 = load i64* %12, align 8
  %14 = load %struct.node** %iplus_addr, align 8
  %15 = getelementptr inbounds %struct.node* %14, i32 0, i32 10
  %16 = load i64* %15, align 8
  %17 = icmp sgt i64 %13, %16
  br i1 %17, label %bb3, label %bb4

bb3:                                              ; preds = %bb2
  %18 = load %struct.node** %iplus_addr, align 8
  store %struct.node* %18, %struct.node** %iminus, align 8
  %19 = load %struct.node** %iplus_addr, align 8
  %20 = getelementptr inbounds %struct.node* %19, i32 0, i32 10
  %21 = load i64* %20, align 8
  %22 = load i64** %delta_addr, align 8
  store i64 %21, i64* %22, align 8
  %23 = load i64** %xchange_addr, align 8
  store i64 0, i64* %23, align 8
  br label %bb4

bb4:                                              ; preds = %bb3, %bb2
  br label %bb8

bb5:                                              ; preds = %bb1
  %24 = load %struct.node** %iplus_addr, align 8
  %25 = getelementptr inbounds %struct.node* %24, i32 0, i32 3
  %26 = load %struct.node** %25, align 8
  %27 = getelementptr inbounds %struct.node* %26, i32 0, i32 3
  %28 = load %struct.node** %27, align 8
  %29 = icmp ne %struct.node* %28, null
  br i1 %29, label %bb6, label %bb8

bb6:                                              ; preds = %bb5
  %30 = load i64** %delta_addr, align 8
  %31 = load i64* %30, align 8
  %32 = load %struct.node** %iplus_addr, align 8
  %33 = getelementptr inbounds %struct.node* %32, i32 0, i32 10
  %34 = load i64* %33, align 8
  %35 = sub nsw i64 1, %34
  %36 = icmp sgt i64 %31, %35
  br i1 %36, label %bb7, label %bb8

bb7:                                              ; preds = %bb6
  %37 = load %struct.node** %iplus_addr, align 8
  store %struct.node* %37, %struct.node** %iminus, align 8
  %38 = load %struct.node** %iplus_addr, align 8
  %39 = getelementptr inbounds %struct.node* %38, i32 0, i32 10
  %40 = load i64* %39, align 8
  %41 = sub nsw i64 1, %40
  %42 = load i64** %delta_addr, align 8
  store i64 %41, i64* %42, align 8
  %43 = load i64** %xchange_addr, align 8
  store i64 0, i64* %43, align 8
  br label %bb8

bb8:                                              ; preds = %bb7, %bb6, %bb5, %bb4
  %44 = load %struct.node** %iplus_addr, align 8
  %45 = getelementptr inbounds %struct.node* %44, i32 0, i32 3
  %46 = load %struct.node** %45, align 8
  store %struct.node* %46, %struct.node** %iplus_addr, align 8
  br label %bb17

bb9:                                              ; preds = %bb
  %47 = load %struct.node** %jplus_addr, align 8
  %48 = getelementptr inbounds %struct.node* %47, i32 0, i32 1
  %49 = load i32* %48, align 8
  %50 = icmp eq i32 %49, 0
  br i1 %50, label %bb10, label %bb13

bb10:                                             ; preds = %bb9
  %51 = load i64** %delta_addr, align 8
  %52 = load i64* %51, align 8
  %53 = load %struct.node** %jplus_addr, align 8
  %54 = getelementptr inbounds %struct.node* %53, i32 0, i32 10
  %55 = load i64* %54, align 8
  %56 = icmp sge i64 %52, %55
  br i1 %56, label %bb11, label %bb12

bb11:                                             ; preds = %bb10
  %57 = load %struct.node** %jplus_addr, align 8
  store %struct.node* %57, %struct.node** %iminus, align 8
  %58 = load %struct.node** %jplus_addr, align 8
  %59 = getelementptr inbounds %struct.node* %58, i32 0, i32 10
  %60 = load i64* %59, align 8
  %61 = load i64** %delta_addr, align 8
  store i64 %60, i64* %61, align 8
  %62 = load i64** %xchange_addr, align 8
  store i64 1, i64* %62, align 8
  br label %bb12

bb12:                                             ; preds = %bb11, %bb10
  br label %bb16

bb13:                                             ; preds = %bb9
  %63 = load %struct.node** %jplus_addr, align 8
  %64 = getelementptr inbounds %struct.node* %63, i32 0, i32 3
  %65 = load %struct.node** %64, align 8
  %66 = getelementptr inbounds %struct.node* %65, i32 0, i32 3
  %67 = load %struct.node** %66, align 8
  %68 = icmp ne %struct.node* %67, null
  br i1 %68, label %bb14, label %bb16

bb14:                                             ; preds = %bb13
  %69 = load i64** %delta_addr, align 8
  %70 = load i64* %69, align 8
  %71 = load %struct.node** %jplus_addr, align 8
  %72 = getelementptr inbounds %struct.node* %71, i32 0, i32 10
  %73 = load i64* %72, align 8
  %74 = sub nsw i64 1, %73
  %75 = icmp sge i64 %70, %74
  br i1 %75, label %bb15, label %bb16

bb15:                                             ; preds = %bb14
  %76 = load %struct.node** %jplus_addr, align 8
  store %struct.node* %76, %struct.node** %iminus, align 8
  %77 = load %struct.node** %jplus_addr, align 8
  %78 = getelementptr inbounds %struct.node* %77, i32 0, i32 10
  %79 = load i64* %78, align 8
  %80 = sub nsw i64 1, %79
  %81 = load i64** %delta_addr, align 8
  store i64 %80, i64* %81, align 8
  %82 = load i64** %xchange_addr, align 8
  store i64 1, i64* %82, align 8
  br label %bb16

bb16:                                             ; preds = %bb15, %bb14, %bb13, %bb12
  %83 = load %struct.node** %jplus_addr, align 8
  %84 = getelementptr inbounds %struct.node* %83, i32 0, i32 3
  %85 = load %struct.node** %84, align 8
  store %struct.node* %85, %struct.node** %jplus_addr, align 8
  br label %bb17

bb17:                                             ; preds = %bb16, %bb8, %entry
  %86 = load %struct.node** %iplus_addr, align 8
  %87 = load %struct.node** %jplus_addr, align 8
  %88 = icmp ne %struct.node* %86, %87
  br i1 %88, label %bb, label %bb18

bb18:                                             ; preds = %bb17
  %89 = load %struct.node*** %w_addr, align 8
  %90 = load %struct.node** %iplus_addr, align 8
  store %struct.node* %90, %struct.node** %89, align 8
  %91 = load %struct.node** %iminus, align 8
  store %struct.node* %91, %struct.node** %0, align 8
  %92 = load %struct.node** %0, align 8
  store %struct.node* %92, %struct.node** %retval, align 8
  br label %return

return:                                           ; preds = %bb18
  %retval19 = load %struct.node** %retval
  ret %struct.node* %retval19
}

define void @primal_update_flow(%struct.node* %iplus, %struct.node* %jplus, %struct.node* %w) nounwind {
entry:
  %iplus_addr = alloca %struct.node*, align 8
  %jplus_addr = alloca %struct.node*, align 8
  %w_addr = alloca %struct.node*, align 8
  %"alloca point" = bitcast i32 0 to i32
  store %struct.node* %iplus, %struct.node** %iplus_addr
  store %struct.node* %jplus, %struct.node** %jplus_addr
  store %struct.node* %w, %struct.node** %w_addr
  br label %bb4

bb:                                               ; preds = %bb4
  %0 = load %struct.node** %iplus_addr, align 8
  %1 = getelementptr inbounds %struct.node* %0, i32 0, i32 1
  %2 = load i32* %1, align 8
  %3 = icmp ne i32 %2, 0
  br i1 %3, label %bb1, label %bb2

bb1:                                              ; preds = %bb
  %4 = load %struct.node** %iplus_addr, align 8
  %5 = getelementptr inbounds %struct.node* %4, i32 0, i32 10
  store i64 0, i64* %5, align 8
  br label %bb3

bb2:                                              ; preds = %bb
  %6 = load %struct.node** %iplus_addr, align 8
  %7 = getelementptr inbounds %struct.node* %6, i32 0, i32 10
  store i64 1, i64* %7, align 8
  br label %bb3

bb3:                                              ; preds = %bb2, %bb1
  %8 = load %struct.node** %iplus_addr, align 8
  %9 = getelementptr inbounds %struct.node* %8, i32 0, i32 3
  %10 = load %struct.node** %9, align 8
  store %struct.node* %10, %struct.node** %iplus_addr, align 8
  br label %bb4

bb4:                                              ; preds = %bb3, %entry
  %11 = load %struct.node** %iplus_addr, align 8
  %12 = load %struct.node** %w_addr, align 8
  %13 = icmp ne %struct.node* %11, %12
  br i1 %13, label %bb, label %bb5

bb5:                                              ; preds = %bb4
  br label %bb10

bb6:                                              ; preds = %bb10
  %14 = load %struct.node** %jplus_addr, align 8
  %15 = getelementptr inbounds %struct.node* %14, i32 0, i32 1
  %16 = load i32* %15, align 8
  %17 = icmp ne i32 %16, 0
  br i1 %17, label %bb7, label %bb8

bb7:                                              ; preds = %bb6
  %18 = load %struct.node** %jplus_addr, align 8
  %19 = getelementptr inbounds %struct.node* %18, i32 0, i32 10
  store i64 1, i64* %19, align 8
  br label %bb9

bb8:                                              ; preds = %bb6
  %20 = load %struct.node** %jplus_addr, align 8
  %21 = getelementptr inbounds %struct.node* %20, i32 0, i32 10
  store i64 0, i64* %21, align 8
  br label %bb9

bb9:                                              ; preds = %bb8, %bb7
  %22 = load %struct.node** %jplus_addr, align 8
  %23 = getelementptr inbounds %struct.node* %22, i32 0, i32 3
  %24 = load %struct.node** %23, align 8
  store %struct.node* %24, %struct.node** %jplus_addr, align 8
  br label %bb10

bb10:                                             ; preds = %bb9, %bb5
  %25 = load %struct.node** %jplus_addr, align 8
  %26 = load %struct.node** %w_addr, align 8
  %27 = icmp ne %struct.node* %25, %26
  br i1 %27, label %bb6, label %bb11

bb11:                                             ; preds = %bb10
  br label %return

return:                                           ; preds = %bb11
  ret void
}

define i64 @primal_net_simplex(%struct.network_t* %net) nounwind {
entry:
  %net_addr = alloca %struct.network_t*, align 8
  %retval = alloca i64
  %0 = alloca i64
  %delta = alloca i64
  %new_flow = alloca i64
  %opt = alloca i64
  %xchange = alloca i64
  %new_orientation = alloca i64
  %iplus = alloca %struct.node*
  %jplus = alloca %struct.node*
  %iminus = alloca %struct.node*
  %jminus = alloca %struct.node*
  %w = alloca %struct.node*
  %bea = alloca %struct.arc*
  %bla = alloca %struct.arc*
  %arcs = alloca %struct.arc*
  %stop_arcs = alloca %struct.arc*
  %temp = alloca %struct.node*
  %m = alloca i64
  %new_set = alloca i64
  %red_cost_of_bea = alloca i64
  %iterations = alloca i64*
  %bound_exchanges = alloca i64*
  %checksum = alloca i64*
  %"alloca point" = bitcast i32 0 to i32
  store %struct.network_t* %net, %struct.network_t** %net_addr
  store i64 0, i64* %opt, align 8
  %1 = load %struct.network_t** %net_addr, align 8
  %2 = getelementptr inbounds %struct.network_t* %1, i32 0, i32 23
  %3 = load %struct.arc** %2, align 8
  store %struct.arc* %3, %struct.arc** %arcs, align 8
  %4 = load %struct.network_t** %net_addr, align 8
  %5 = getelementptr inbounds %struct.network_t* %4, i32 0, i32 24
  %6 = load %struct.arc** %5, align 8
  store %struct.arc* %6, %struct.arc** %stop_arcs, align 8
  %7 = load %struct.network_t** %net_addr, align 8
  %8 = getelementptr inbounds %struct.network_t* %7, i32 0, i32 5
  %9 = load i64* %8, align 8
  store i64 %9, i64* %m, align 8
  %10 = load %struct.network_t** %net_addr, align 8
  %11 = getelementptr inbounds %struct.network_t* %10, i32 0, i32 27
  store i64* %11, i64** %iterations, align 8
  %12 = load %struct.network_t** %net_addr, align 8
  %13 = getelementptr inbounds %struct.network_t* %12, i32 0, i32 28
  store i64* %13, i64** %bound_exchanges, align 8
  %14 = load %struct.network_t** %net_addr, align 8
  %15 = getelementptr inbounds %struct.network_t* %14, i32 0, i32 29
  store i64* %15, i64** %checksum, align 8
  br label %bb26

bb:                                               ; preds = %bb26
  %16 = load i64* %m, align 8
  %17 = load %struct.arc** %arcs, align 8
  %18 = load %struct.arc** %stop_arcs, align 8
  %19 = call %struct.arc* @primal_bea_mpp(i64 %16, %struct.arc* %17, %struct.arc* %18, i64* %red_cost_of_bea) nounwind
  store %struct.arc* %19, %struct.arc** %bea, align 8
  %20 = load %struct.arc** %bea, align 8
  %21 = icmp ne %struct.arc* %20, null
  br i1 %21, label %bb1, label %bb25

bb1:                                              ; preds = %bb
  %22 = load i64** %iterations, align 8
  %23 = load i64* %22, align 8
  %24 = add nsw i64 %23, 1
  %25 = load i64** %iterations, align 8
  store i64 %24, i64* %25, align 8
  %26 = load i64* %red_cost_of_bea, align 8
  %27 = icmp sgt i64 %26, 0
  br i1 %27, label %bb2, label %bb3

bb2:                                              ; preds = %bb1
  %28 = load %struct.arc** %bea, align 8
  %29 = getelementptr inbounds %struct.arc* %28, i32 0, i32 2
  %30 = load %struct.node** %29, align 8
  store %struct.node* %30, %struct.node** %iplus, align 8
  %31 = load %struct.arc** %bea, align 8
  %32 = getelementptr inbounds %struct.arc* %31, i32 0, i32 1
  %33 = load %struct.node** %32, align 8
  store %struct.node* %33, %struct.node** %jplus, align 8
  br label %bb4

bb3:                                              ; preds = %bb1
  %34 = load %struct.arc** %bea, align 8
  %35 = getelementptr inbounds %struct.arc* %34, i32 0, i32 1
  %36 = load %struct.node** %35, align 8
  store %struct.node* %36, %struct.node** %iplus, align 8
  %37 = load %struct.arc** %bea, align 8
  %38 = getelementptr inbounds %struct.arc* %37, i32 0, i32 2
  %39 = load %struct.node** %38, align 8
  store %struct.node* %39, %struct.node** %jplus, align 8
  br label %bb4

bb4:                                              ; preds = %bb3, %bb2
  store i64 1, i64* %delta, align 8
  %40 = load %struct.node** %iplus, align 8
  %41 = load %struct.node** %jplus, align 8
  %42 = call %struct.node* @primal_iminus(i64* %delta, i64* %xchange, %struct.node* %40, %struct.node* %41, %struct.node** %w) nounwind
  store %struct.node* %42, %struct.node** %iminus, align 8
  %43 = load %struct.node** %iminus, align 8
  %44 = icmp eq %struct.node* %43, null
  br i1 %44, label %bb5, label %bb11

bb5:                                              ; preds = %bb4
  %45 = load i64** %bound_exchanges, align 8
  %46 = load i64* %45, align 8
  %47 = add nsw i64 %46, 1
  %48 = load i64** %bound_exchanges, align 8
  store i64 %47, i64* %48, align 8
  %49 = load %struct.arc** %bea, align 8
  %50 = getelementptr inbounds %struct.arc* %49, i32 0, i32 3
  %51 = load i32* %50, align 8
  %52 = icmp eq i32 %51, 2
  br i1 %52, label %bb6, label %bb7

bb6:                                              ; preds = %bb5
  %53 = load %struct.arc** %bea, align 8
  %54 = getelementptr inbounds %struct.arc* %53, i32 0, i32 3
  store i32 1, i32* %54, align 8
  br label %bb8

bb7:                                              ; preds = %bb5
  %55 = load %struct.arc** %bea, align 8
  %56 = getelementptr inbounds %struct.arc* %55, i32 0, i32 3
  store i32 2, i32* %56, align 8
  br label %bb8

bb8:                                              ; preds = %bb7, %bb6
  %57 = load i64* %delta, align 8
  %58 = icmp ne i64 %57, 0
  br i1 %58, label %bb9, label %bb10

bb9:                                              ; preds = %bb8
  %59 = load %struct.node** %w, align 8
  %60 = load %struct.node** %iplus, align 8
  %61 = load %struct.node** %jplus, align 8
  call void @primal_update_flow(%struct.node* %60, %struct.node* %61, %struct.node* %59) nounwind
  br label %bb10

bb10:                                             ; preds = %bb9, %bb8
  br label %bb24

bb11:                                             ; preds = %bb4
  %62 = load i64* %xchange, align 8
  %63 = icmp ne i64 %62, 0
  br i1 %63, label %bb12, label %bb13

bb12:                                             ; preds = %bb11
  %64 = load %struct.node** %jplus, align 8
  store %struct.node* %64, %struct.node** %temp, align 8
  %65 = load %struct.node** %iplus, align 8
  store %struct.node* %65, %struct.node** %jplus, align 8
  %66 = load %struct.node** %temp, align 8
  store %struct.node* %66, %struct.node** %iplus, align 8
  br label %bb13

bb13:                                             ; preds = %bb12, %bb11
  %67 = load %struct.node** %iminus, align 8
  %68 = getelementptr inbounds %struct.node* %67, i32 0, i32 3
  %69 = load %struct.node** %68, align 8
  store %struct.node* %69, %struct.node** %jminus, align 8
  %70 = load %struct.node** %iminus, align 8
  %71 = getelementptr inbounds %struct.node* %70, i32 0, i32 6
  %72 = load %struct.arc** %71, align 8
  store %struct.arc* %72, %struct.arc** %bla, align 8
  %73 = load %struct.node** %iminus, align 8
  %74 = getelementptr inbounds %struct.node* %73, i32 0, i32 1
  %75 = load i32* %74, align 8
  %76 = sext i32 %75 to i64
  %77 = load i64* %xchange, align 8
  %78 = icmp ne i64 %76, %77
  br i1 %78, label %bb14, label %bb15

bb14:                                             ; preds = %bb13
  store i64 1, i64* %new_set, align 8
  br label %bb16

bb15:                                             ; preds = %bb13
  store i64 2, i64* %new_set, align 8
  br label %bb16

bb16:                                             ; preds = %bb15, %bb14
  %79 = load i64* %red_cost_of_bea, align 8
  %80 = icmp sgt i64 %79, 0
  br i1 %80, label %bb17, label %bb18

bb17:                                             ; preds = %bb16
  %81 = load i64* %delta, align 8
  %82 = sub nsw i64 1, %81
  store i64 %82, i64* %new_flow, align 8
  br label %bb19

bb18:                                             ; preds = %bb16
  %83 = load i64* %delta, align 8
  store i64 %83, i64* %new_flow, align 8
  br label %bb19

bb19:                                             ; preds = %bb18, %bb17
  %84 = load %struct.arc** %bea, align 8
  %85 = getelementptr inbounds %struct.arc* %84, i32 0, i32 1
  %86 = load %struct.node** %85, align 8
  %87 = load %struct.node** %iplus, align 8
  %88 = icmp eq %struct.node* %86, %87
  br i1 %88, label %bb20, label %bb21

bb20:                                             ; preds = %bb19
  store i64 1, i64* %new_orientation, align 8
  br label %bb22

bb21:                                             ; preds = %bb19
  store i64 0, i64* %new_orientation, align 8
  br label %bb22

bb22:                                             ; preds = %bb21, %bb20
  %89 = load %struct.network_t** %net_addr, align 8
  %90 = getelementptr inbounds %struct.network_t* %89, i32 0, i32 16
  %91 = load i64* %90, align 8
  %92 = load i64* %red_cost_of_bea, align 8
  %93 = load %struct.node** %w, align 8
  %94 = load i64* %delta, align 8
  %95 = load i64* %xchange, align 8
  %96 = icmp eq i64 %95, 0
  %97 = zext i1 %96 to i64
  %98 = load i64* %new_orientation, align 8
  %99 = load i64* %new_flow, align 8
  %100 = load %struct.node** %iplus, align 8
  %101 = load %struct.node** %jplus, align 8
  %102 = load %struct.node** %iminus, align 8
  %103 = load %struct.node** %jminus, align 8
  %104 = load %struct.arc** %bea, align 8
  call void @update_tree(i64 %97, i64 %98, i64 %94, i64 %99, %struct.node* %100, %struct.node* %101, %struct.node* %102, %struct.node* %103, %struct.node* %93, %struct.arc* %104, i64 %92, i64 %91) nounwind
  %105 = load %struct.arc** %bea, align 8
  %106 = getelementptr inbounds %struct.arc* %105, i32 0, i32 3
  store i32 0, i32* %106, align 8
  %107 = load i64* %new_set, align 8
  %108 = trunc i64 %107 to i32
  %109 = load %struct.arc** %bla, align 8
  %110 = getelementptr inbounds %struct.arc* %109, i32 0, i32 3
  store i32 %108, i32* %110, align 8
  %111 = load i64** %iterations, align 8
  %112 = load i64* %111, align 8
  %113 = sub nsw i64 %112, 1
  %114 = srem i64 %113, 200
  %115 = icmp eq i64 %114, 0
  br i1 %115, label %bb23, label %bb24

bb23:                                             ; preds = %bb22
  %116 = load i64** %checksum, align 8
  %117 = load i64* %116, align 8
  %118 = load %struct.network_t** %net_addr, align 8
  %119 = call i64 @refresh_potential(%struct.network_t* %118) nounwind
  %120 = add nsw i64 %117, %119
  %121 = load i64** %checksum, align 8
  store i64 %120, i64* %121, align 8
  br label %bb24

bb24:                                             ; preds = %bb23, %bb22, %bb10
  br label %bb26

bb25:                                             ; preds = %bb
  store i64 1, i64* %opt, align 8
  br label %bb26

bb26:                                             ; preds = %bb25, %bb24, %entry
  %122 = load i64* %opt, align 8
  %123 = icmp eq i64 %122, 0
  br i1 %123, label %bb, label %bb27

bb27:                                             ; preds = %bb26
  %124 = load i64** %checksum, align 8
  %125 = load i64* %124, align 8
  %126 = load %struct.network_t** %net_addr, align 8
  %127 = call i64 @refresh_potential(%struct.network_t* %126) nounwind
  %128 = add nsw i64 %125, %127
  %129 = load i64** %checksum, align 8
  store i64 %128, i64* %129, align 8
  %130 = load %struct.network_t** %net_addr, align 8
  %131 = call i64 @primal_feasible(%struct.network_t* %130) nounwind
  %132 = load %struct.network_t** %net_addr, align 8
  %133 = call i64 @dual_feasible(%struct.network_t* %132) nounwind
  store i64 0, i64* %0, align 8
  %134 = load i64* %0, align 8
  store i64 %134, i64* %retval, align 8
  br label %return

return:                                           ; preds = %bb27
  %retval28 = load i64* %retval
  ret i64 %retval28
}

define i64 @primal_start_artificial(%struct.network_t* %net) nounwind {
entry:
  %net_addr = alloca %struct.network_t*, align 8
  %retval = alloca i64
  %0 = alloca i64
  %node = alloca %struct.node*
  %root = alloca %struct.node*
  %arc = alloca %struct.arc*
  %stop = alloca i8*
  %"alloca point" = bitcast i32 0 to i32
  store %struct.network_t* %net, %struct.network_t** %net_addr
  %1 = load %struct.network_t** %net_addr, align 8
  %2 = getelementptr inbounds %struct.network_t* %1, i32 0, i32 21
  %3 = load %struct.node** %2, align 8
  store %struct.node* %3, %struct.node** %node, align 8
  %4 = load %struct.node** %node, align 8
  store %struct.node* %4, %struct.node** %root, align 8
  %5 = load %struct.node** %node, align 8
  %6 = getelementptr inbounds %struct.node* %5, i64 1
  store %struct.node* %6, %struct.node** %node, align 8
  %7 = load %struct.node** %root, align 8
  %8 = getelementptr inbounds %struct.node* %7, i32 0, i32 6
  store %struct.arc* null, %struct.arc** %8, align 8
  %9 = load %struct.node** %root, align 8
  %10 = getelementptr inbounds %struct.node* %9, i32 0, i32 3
  store %struct.node* null, %struct.node** %10, align 8
  %11 = load %struct.node** %root, align 8
  %12 = getelementptr inbounds %struct.node* %11, i32 0, i32 2
  %13 = load %struct.node** %node, align 8
  store %struct.node* %13, %struct.node** %12, align 8
  %14 = load %struct.node** %root, align 8
  %15 = getelementptr inbounds %struct.node* %14, i32 0, i32 4
  store %struct.node* null, %struct.node** %15, align 8
  %16 = load %struct.node** %root, align 8
  %17 = getelementptr inbounds %struct.node* %16, i32 0, i32 5
  store %struct.node* null, %struct.node** %17, align 8
  %18 = load %struct.network_t** %net_addr, align 8
  %19 = getelementptr inbounds %struct.network_t* %18, i32 0, i32 2
  %20 = load i64* %19, align 8
  %21 = add nsw i64 %20, 1
  %22 = load %struct.node** %root, align 8
  %23 = getelementptr inbounds %struct.node* %22, i32 0, i32 11
  store i64 %21, i64* %23, align 8
  %24 = load %struct.node** %root, align 8
  %25 = getelementptr inbounds %struct.node* %24, i32 0, i32 1
  store i32 0, i32* %25, align 8
  %26 = load %struct.node** %root, align 8
  %27 = getelementptr inbounds %struct.node* %26, i32 0, i32 0
  store i64 -100000000, i64* %27, align 8
  %28 = load %struct.node** %root, align 8
  %29 = getelementptr inbounds %struct.node* %28, i32 0, i32 10
  store i64 0, i64* %29, align 8
  %30 = load %struct.network_t** %net_addr, align 8
  %31 = getelementptr inbounds %struct.network_t* %30, i32 0, i32 24
  %32 = load %struct.arc** %31, align 8
  %33 = bitcast %struct.arc* %32 to i8*
  store i8* %33, i8** %stop, align 8
  %34 = load %struct.network_t** %net_addr, align 8
  %35 = getelementptr inbounds %struct.network_t* %34, i32 0, i32 23
  %36 = load %struct.arc** %35, align 8
  store %struct.arc* %36, %struct.arc** %arc, align 8
  br label %bb3

bb:                                               ; preds = %bb3
  %37 = load %struct.arc** %arc, align 8
  %38 = getelementptr inbounds %struct.arc* %37, i32 0, i32 3
  %39 = load i32* %38, align 8
  %40 = icmp ne i32 %39, -1
  br i1 %40, label %bb1, label %bb2

bb1:                                              ; preds = %bb
  %41 = load %struct.arc** %arc, align 8
  %42 = getelementptr inbounds %struct.arc* %41, i32 0, i32 3
  store i32 1, i32* %42, align 8
  br label %bb2

bb2:                                              ; preds = %bb1, %bb
  %43 = load %struct.arc** %arc, align 8
  %44 = getelementptr inbounds %struct.arc* %43, i64 1
  store %struct.arc* %44, %struct.arc** %arc, align 8
  br label %bb3

bb3:                                              ; preds = %bb2, %entry
  %45 = load i8** %stop, align 8
  %46 = bitcast i8* %45 to %struct.arc*
  %47 = load %struct.arc** %arc, align 8
  %48 = icmp ne %struct.arc* %47, %46
  br i1 %48, label %bb, label %bb4

bb4:                                              ; preds = %bb3
  %49 = load %struct.network_t** %net_addr, align 8
  %50 = getelementptr inbounds %struct.network_t* %49, i32 0, i32 25
  %51 = load %struct.arc** %50, align 8
  store %struct.arc* %51, %struct.arc** %arc, align 8
  %52 = load %struct.network_t** %net_addr, align 8
  %53 = getelementptr inbounds %struct.network_t* %52, i32 0, i32 22
  %54 = load %struct.node** %53, align 8
  %55 = bitcast %struct.node* %54 to i8*
  store i8* %55, i8** %stop, align 8
  br label %bb6

bb5:                                              ; preds = %bb6
  %56 = load %struct.node** %node, align 8
  %57 = getelementptr inbounds %struct.node* %56, i32 0, i32 6
  %58 = load %struct.arc** %arc, align 8
  store %struct.arc* %58, %struct.arc** %57, align 8
  %59 = load %struct.node** %node, align 8
  %60 = getelementptr inbounds %struct.node* %59, i32 0, i32 3
  %61 = load %struct.node** %root, align 8
  store %struct.node* %61, %struct.node** %60, align 8
  %62 = load %struct.node** %node, align 8
  %63 = getelementptr inbounds %struct.node* %62, i32 0, i32 2
  store %struct.node* null, %struct.node** %63, align 8
  %64 = load %struct.node** %node, align 8
  %65 = getelementptr inbounds %struct.node* %64, i64 1
  %66 = load %struct.node** %node, align 8
  %67 = getelementptr inbounds %struct.node* %66, i32 0, i32 4
  store %struct.node* %65, %struct.node** %67, align 8
  %68 = load %struct.node** %node, align 8
  %69 = getelementptr inbounds %struct.node* %68, i64 -1
  %70 = load %struct.node** %node, align 8
  %71 = getelementptr inbounds %struct.node* %70, i32 0, i32 5
  store %struct.node* %69, %struct.node** %71, align 8
  %72 = load %struct.node** %node, align 8
  %73 = getelementptr inbounds %struct.node* %72, i32 0, i32 11
  store i64 1, i64* %73, align 8
  %74 = load %struct.arc** %arc, align 8
  %75 = getelementptr inbounds %struct.arc* %74, i32 0, i32 0
  store i64 100000000, i64* %75, align 8
  %76 = load %struct.arc** %arc, align 8
  %77 = getelementptr inbounds %struct.arc* %76, i32 0, i32 3
  store i32 0, i32* %77, align 8
  %78 = load %struct.node** %node, align 8
  %79 = getelementptr inbounds %struct.node* %78, i32 0, i32 1
  store i32 1, i32* %79, align 8
  %80 = load %struct.node** %node, align 8
  %81 = getelementptr inbounds %struct.node* %80, i32 0, i32 0
  store i64 0, i64* %81, align 8
  %82 = load %struct.arc** %arc, align 8
  %83 = getelementptr inbounds %struct.arc* %82, i32 0, i32 1
  %84 = load %struct.node** %node, align 8
  store %struct.node* %84, %struct.node** %83, align 8
  %85 = load %struct.arc** %arc, align 8
  %86 = getelementptr inbounds %struct.arc* %85, i32 0, i32 2
  %87 = load %struct.node** %root, align 8
  store %struct.node* %87, %struct.node** %86, align 8
  %88 = load %struct.node** %node, align 8
  %89 = getelementptr inbounds %struct.node* %88, i32 0, i32 10
  store i64 0, i64* %89, align 8
  %90 = load %struct.arc** %arc, align 8
  %91 = getelementptr inbounds %struct.arc* %90, i64 1
  store %struct.arc* %91, %struct.arc** %arc, align 8
  %92 = load %struct.node** %node, align 8
  %93 = getelementptr inbounds %struct.node* %92, i64 1
  store %struct.node* %93, %struct.node** %node, align 8
  br label %bb6

bb6:                                              ; preds = %bb5, %bb4
  %94 = load i8** %stop, align 8
  %95 = bitcast i8* %94 to %struct.node*
  %96 = load %struct.node** %node, align 8
  %97 = icmp ne %struct.node* %96, %95
  br i1 %97, label %bb5, label %bb7

bb7:                                              ; preds = %bb6
  %98 = load %struct.node** %node, align 8
  %99 = getelementptr inbounds %struct.node* %98, i64 -1
  store %struct.node* %99, %struct.node** %node, align 8
  %100 = load %struct.node** %root, align 8
  %101 = getelementptr inbounds %struct.node* %100, i64 1
  store %struct.node* %101, %struct.node** %root, align 8
  %102 = load %struct.node** %node, align 8
  %103 = getelementptr inbounds %struct.node* %102, i32 0, i32 4
  store %struct.node* null, %struct.node** %103, align 8
  %104 = load %struct.node** %root, align 8
  %105 = getelementptr inbounds %struct.node* %104, i32 0, i32 5
  store %struct.node* null, %struct.node** %105, align 8
  store i64 0, i64* %0, align 8
  %106 = load i64* %0, align 8
  store i64 %106, i64* %retval, align 8
  br label %return

return:                                           ; preds = %bb7
  %retval8 = load i64* %retval
  ret i64 %retval8
}

define i64 @read_min(%struct.network_t* %net) nounwind {
entry:
  %net_addr = alloca %struct.network_t*, align 8
  %retval = alloca i64
  %0 = alloca i64
  %in = alloca %struct.FILE*
  %instring = alloca [201 x i8]
  %t = alloca i64
  %h = alloca i64
  %c = alloca i64
  %i = alloca i64
  %arc = alloca %struct.arc*
  %node = alloca %struct.node*
  %"alloca point" = bitcast i32 0 to i32
  store %struct.network_t* %net, %struct.network_t** %net_addr
  store %struct.FILE* null, %struct.FILE** %in, align 8
  %1 = load %struct.network_t** %net_addr, align 8
  %2 = getelementptr inbounds %struct.network_t* %1, i32 0, i32 0
  %3 = getelementptr inbounds [200 x i8]* %2, i64 0, i64 0
  %4 = call %struct.FILE* @fopen(i8* noalias %3, i8* noalias getelementptr inbounds ([2 x i8]* @.str30, i64 0, i64 0)) nounwind
  store %struct.FILE* %4, %struct.FILE** %in, align 8
  %5 = load %struct.FILE** %in, align 8
  %6 = icmp eq %struct.FILE* %5, null
  br i1 %6, label %bb, label %bb1

bb:                                               ; preds = %entry
  store i64 -1, i64* %0, align 8
  br label %bb45

bb1:                                              ; preds = %entry
  %instring2 = bitcast [201 x i8]* %instring to i8*
  %7 = load %struct.FILE** %in, align 8
  %8 = call i8* @fgets(i8* noalias %instring2, i32 200, %struct.FILE* noalias %7) nounwind
  %instring3 = bitcast [201 x i8]* %instring to i8*
  %9 = call i32 (i8*, i8*, ...)* @"\01__isoc99_sscanf"(i8* noalias %instring3, i8* noalias getelementptr inbounds ([8 x i8]* @.str131, i64 0, i64 0), i64* %t, i64* %h) nounwind
  %10 = icmp ne i32 %9, 2
  br i1 %10, label %bb4, label %bb5

bb4:                                              ; preds = %bb1
  store i64 -1, i64* %0, align 8
  br label %bb45

bb5:                                              ; preds = %bb1
  %11 = load i64* %t, align 8
  %12 = load %struct.network_t** %net_addr, align 8
  %13 = getelementptr inbounds %struct.network_t* %12, i32 0, i32 3
  store i64 %11, i64* %13, align 8
  %14 = load i64* %h, align 8
  %15 = load %struct.network_t** %net_addr, align 8
  %16 = getelementptr inbounds %struct.network_t* %15, i32 0, i32 6
  store i64 %14, i64* %16, align 8
  %17 = load i64* %t, align 8
  %18 = load i64* %t, align 8
  %19 = add nsw i64 %17, %18
  %20 = add nsw i64 %19, 1
  %21 = load %struct.network_t** %net_addr, align 8
  %22 = getelementptr inbounds %struct.network_t* %21, i32 0, i32 2
  store i64 %20, i64* %22, align 8
  %23 = load i64* %t, align 8
  %24 = load i64* %t, align 8
  %25 = add nsw i64 %23, %24
  %26 = load i64* %t, align 8
  %27 = add nsw i64 %25, %26
  %28 = load i64* %h, align 8
  %29 = add nsw i64 %27, %28
  %30 = load %struct.network_t** %net_addr, align 8
  %31 = getelementptr inbounds %struct.network_t* %30, i32 0, i32 5
  store i64 %29, i64* %31, align 8
  %32 = load %struct.network_t** %net_addr, align 8
  %33 = getelementptr inbounds %struct.network_t* %32, i32 0, i32 3
  %34 = load i64* %33, align 8
  %35 = icmp sle i64 %34, 15000
  br i1 %35, label %bb6, label %bb7

bb6:                                              ; preds = %bb5
  %36 = load %struct.network_t** %net_addr, align 8
  %37 = getelementptr inbounds %struct.network_t* %36, i32 0, i32 5
  %38 = load i64* %37, align 8
  %39 = load %struct.network_t** %net_addr, align 8
  %40 = getelementptr inbounds %struct.network_t* %39, i32 0, i32 4
  store i64 %38, i64* %40, align 8
  %41 = load %struct.network_t** %net_addr, align 8
  %42 = getelementptr inbounds %struct.network_t* %41, i32 0, i32 9
  store i64 3000000, i64* %42, align 8
  br label %bb8

bb7:                                              ; preds = %bb5
  %43 = load %struct.network_t** %net_addr, align 8
  %44 = getelementptr inbounds %struct.network_t* %43, i32 0, i32 4
  store i64 27328512, i64* %44, align 8
  %45 = load %struct.network_t** %net_addr, align 8
  %46 = getelementptr inbounds %struct.network_t* %45, i32 0, i32 9
  store i64 28900000, i64* %46, align 8
  br label %bb8

bb8:                                              ; preds = %bb7, %bb6
  %47 = load %struct.network_t** %net_addr, align 8
  %48 = getelementptr inbounds %struct.network_t* %47, i32 0, i32 4
  %49 = load i64* %48, align 8
  %50 = load %struct.network_t** %net_addr, align 8
  %51 = getelementptr inbounds %struct.network_t* %50, i32 0, i32 5
  %52 = load i64* %51, align 8
  %53 = sub nsw i64 %49, %52
  %54 = load %struct.network_t** %net_addr, align 8
  %55 = getelementptr inbounds %struct.network_t* %54, i32 0, i32 8
  store i64 %53, i64* %55, align 8
  %56 = load %struct.network_t** %net_addr, align 8
  %57 = getelementptr inbounds %struct.network_t* %56, i32 0, i32 9
  %58 = load i64* %57, align 8
  %59 = icmp sle i64 %58, 2
  br i1 %59, label %bb9, label %bb10

bb9:                                              ; preds = %bb8
  call void @__assert_fail(i8* getelementptr inbounds ([20 x i8]* @.str232, i64 0, i64 0), i8* getelementptr inbounds ([10 x i8]* @.str333, i64 0, i64 0), i32 77, i8* getelementptr inbounds ([9 x i8]* @__PRETTY_FUNCTION__.4370, i64 0, i64 0)) noreturn nounwind
  unreachable

bb10:                                             ; preds = %bb8
  %60 = load %struct.network_t** %net_addr, align 8
  %61 = getelementptr inbounds %struct.network_t* %60, i32 0, i32 2
  %62 = load i64* %61, align 8
  %63 = add nsw i64 %62, 1
  %64 = call noalias i8* @calloc(i64 %63, i64 104) nounwind
  %65 = bitcast i8* %64 to %struct.node*
  %66 = load %struct.network_t** %net_addr, align 8
  %67 = getelementptr inbounds %struct.network_t* %66, i32 0, i32 21
  store %struct.node* %65, %struct.node** %67, align 8
  %68 = load %struct.network_t** %net_addr, align 8
  %69 = getelementptr inbounds %struct.network_t* %68, i32 0, i32 2
  %70 = load i64* %69, align 8
  %71 = call noalias i8* @calloc(i64 %70, i64 64) nounwind
  %72 = bitcast i8* %71 to %struct.arc*
  %73 = load %struct.network_t** %net_addr, align 8
  %74 = getelementptr inbounds %struct.network_t* %73, i32 0, i32 25
  store %struct.arc* %72, %struct.arc** %74, align 8
  %75 = load %struct.network_t** %net_addr, align 8
  %76 = getelementptr inbounds %struct.network_t* %75, i32 0, i32 4
  %77 = load i64* %76, align 8
  %78 = call noalias i8* @calloc(i64 %77, i64 64) nounwind
  %79 = bitcast i8* %78 to %struct.arc*
  %80 = load %struct.network_t** %net_addr, align 8
  %81 = getelementptr inbounds %struct.network_t* %80, i32 0, i32 23
  store %struct.arc* %79, %struct.arc** %81, align 8
  %82 = load %struct.network_t** %net_addr, align 8
  %83 = getelementptr inbounds %struct.network_t* %82, i32 0, i32 21
  %84 = load %struct.node** %83, align 8
  %85 = icmp eq %struct.node* %84, null
  br i1 %85, label %bb13, label %bb11

bb11:                                             ; preds = %bb10
  %86 = load %struct.network_t** %net_addr, align 8
  %87 = getelementptr inbounds %struct.network_t* %86, i32 0, i32 23
  %88 = load %struct.arc** %87, align 8
  %89 = icmp eq %struct.arc* %88, null
  br i1 %89, label %bb13, label %bb12

bb12:                                             ; preds = %bb11
  %90 = load %struct.network_t** %net_addr, align 8
  %91 = getelementptr inbounds %struct.network_t* %90, i32 0, i32 25
  %92 = load %struct.arc** %91, align 8
  %93 = icmp eq %struct.arc* %92, null
  br i1 %93, label %bb13, label %bb14

bb13:                                             ; preds = %bb12, %bb11, %bb10
  %94 = call i32 @puts(i8* getelementptr inbounds ([30 x i8]* @.str434, i64 0, i64 0)) nounwind
  %95 = load %struct.network_t** %net_addr, align 8
  %96 = call i64 @getfree(%struct.network_t* %95) nounwind
  store i64 -1, i64* %0, align 8
  br label %bb45

bb14:                                             ; preds = %bb12
  %97 = load %struct.network_t** %net_addr, align 8
  %98 = getelementptr inbounds %struct.network_t* %97, i32 0, i32 21
  %99 = load %struct.node** %98, align 8
  %100 = load %struct.network_t** %net_addr, align 8
  %101 = getelementptr inbounds %struct.network_t* %100, i32 0, i32 2
  %102 = load i64* %101, align 8
  %103 = getelementptr inbounds %struct.node* %99, i64 %102
  %104 = getelementptr inbounds %struct.node* %103, i64 1
  %105 = load %struct.network_t** %net_addr, align 8
  %106 = getelementptr inbounds %struct.network_t* %105, i32 0, i32 22
  store %struct.node* %104, %struct.node** %106, align 8
  %107 = load %struct.network_t** %net_addr, align 8
  %108 = getelementptr inbounds %struct.network_t* %107, i32 0, i32 23
  %109 = load %struct.arc** %108, align 8
  %110 = load %struct.network_t** %net_addr, align 8
  %111 = getelementptr inbounds %struct.network_t* %110, i32 0, i32 5
  %112 = load i64* %111, align 8
  %113 = getelementptr inbounds %struct.arc* %109, i64 %112
  %114 = load %struct.network_t** %net_addr, align 8
  %115 = getelementptr inbounds %struct.network_t* %114, i32 0, i32 24
  store %struct.arc* %113, %struct.arc** %115, align 8
  %116 = load %struct.network_t** %net_addr, align 8
  %117 = getelementptr inbounds %struct.network_t* %116, i32 0, i32 25
  %118 = load %struct.arc** %117, align 8
  %119 = load %struct.network_t** %net_addr, align 8
  %120 = getelementptr inbounds %struct.network_t* %119, i32 0, i32 2
  %121 = load i64* %120, align 8
  %122 = getelementptr inbounds %struct.arc* %118, i64 %121
  %123 = load %struct.network_t** %net_addr, align 8
  %124 = getelementptr inbounds %struct.network_t* %123, i32 0, i32 26
  store %struct.arc* %122, %struct.arc** %124, align 8
  %125 = load %struct.network_t** %net_addr, align 8
  %126 = getelementptr inbounds %struct.network_t* %125, i32 0, i32 21
  %127 = load %struct.node** %126, align 8
  store %struct.node* %127, %struct.node** %node, align 8
  %128 = load %struct.network_t** %net_addr, align 8
  %129 = getelementptr inbounds %struct.network_t* %128, i32 0, i32 23
  %130 = load %struct.arc** %129, align 8
  store %struct.arc* %130, %struct.arc** %arc, align 8
  store i64 1, i64* %i, align 8
  br label %bb22

bb15:                                             ; preds = %bb22
  %instring16 = bitcast [201 x i8]* %instring to i8*
  %131 = load %struct.FILE** %in, align 8
  %132 = call i8* @fgets(i8* noalias %instring16, i32 200, %struct.FILE* noalias %131) nounwind
  %instring17 = bitcast [201 x i8]* %instring to i8*
  %133 = call i32 (i8*, i8*, ...)* @"\01__isoc99_sscanf"(i8* noalias %instring17, i8* noalias getelementptr inbounds ([8 x i8]* @.str131, i64 0, i64 0), i64* %t, i64* %h) nounwind
  %134 = icmp ne i32 %133, 2
  br i1 %134, label %bb19, label %bb18

bb18:                                             ; preds = %bb15
  %135 = load i64* %t, align 8
  %136 = load i64* %h, align 8
  %137 = icmp sgt i64 %135, %136
  br i1 %137, label %bb19, label %bb20

bb19:                                             ; preds = %bb18, %bb15
  store i64 -1, i64* %0, align 8
  br label %bb45

bb20:                                             ; preds = %bb18
  %138 = load %struct.node** %node, align 8
  %139 = load i64* %i, align 8
  %140 = getelementptr inbounds %struct.node* %138, i64 %139
  %141 = load i64* %i, align 8
  %142 = trunc i64 %141 to i32
  %143 = sub nsw i32 0, %142
  %144 = getelementptr inbounds %struct.node* %140, i32 0, i32 12
  store i32 %143, i32* %144, align 8
  %145 = load %struct.node** %node, align 8
  %146 = load i64* %i, align 8
  %147 = getelementptr inbounds %struct.node* %145, i64 %146
  %148 = getelementptr inbounds %struct.node* %147, i32 0, i32 10
  store i64 -1, i64* %148, align 8
  %149 = load %struct.network_t** %net_addr, align 8
  %150 = getelementptr inbounds %struct.network_t* %149, i32 0, i32 3
  %151 = load i64* %150, align 8
  %152 = load i64* %i, align 8
  %153 = add nsw i64 %151, %152
  %154 = load %struct.node** %node, align 8
  %155 = getelementptr inbounds %struct.node* %154, i64 %153
  %156 = load i64* %i, align 8
  %157 = trunc i64 %156 to i32
  %158 = getelementptr inbounds %struct.node* %155, i32 0, i32 12
  store i32 %157, i32* %158, align 8
  %159 = load %struct.network_t** %net_addr, align 8
  %160 = getelementptr inbounds %struct.network_t* %159, i32 0, i32 3
  %161 = load i64* %160, align 8
  %162 = load i64* %i, align 8
  %163 = add nsw i64 %161, %162
  %164 = load %struct.node** %node, align 8
  %165 = getelementptr inbounds %struct.node* %164, i64 %163
  %166 = getelementptr inbounds %struct.node* %165, i32 0, i32 10
  store i64 1, i64* %166, align 8
  %167 = load %struct.node** %node, align 8
  %168 = load i64* %i, align 8
  %169 = getelementptr inbounds %struct.node* %167, i64 %168
  %170 = load i64* %t, align 8
  %171 = trunc i64 %170 to i32
  %172 = getelementptr inbounds %struct.node* %169, i32 0, i32 13
  store i32 %171, i32* %172, align 4
  %173 = load %struct.network_t** %net_addr, align 8
  %174 = getelementptr inbounds %struct.network_t* %173, i32 0, i32 3
  %175 = load i64* %174, align 8
  %176 = load i64* %i, align 8
  %177 = add nsw i64 %175, %176
  %178 = load %struct.node** %node, align 8
  %179 = getelementptr inbounds %struct.node* %178, i64 %177
  %180 = load i64* %h, align 8
  %181 = trunc i64 %180 to i32
  %182 = getelementptr inbounds %struct.node* %179, i32 0, i32 13
  store i32 %181, i32* %182, align 4
  %183 = load %struct.network_t** %net_addr, align 8
  %184 = getelementptr inbounds %struct.network_t* %183, i32 0, i32 2
  %185 = load i64* %184, align 8
  %186 = load %struct.node** %node, align 8
  %187 = getelementptr inbounds %struct.node* %186, i64 %185
  %188 = load %struct.arc** %arc, align 8
  %189 = getelementptr inbounds %struct.arc* %188, i32 0, i32 1
  store %struct.node* %187, %struct.node** %189, align 8
  %190 = load %struct.node** %node, align 8
  %191 = load i64* %i, align 8
  %192 = getelementptr inbounds %struct.node* %190, i64 %191
  %193 = load %struct.arc** %arc, align 8
  %194 = getelementptr inbounds %struct.arc* %193, i32 0, i32 2
  store %struct.node* %192, %struct.node** %194, align 8
  %195 = load %struct.network_t** %net_addr, align 8
  %196 = getelementptr inbounds %struct.network_t* %195, i32 0, i32 18
  %197 = load i64* %196, align 8
  %198 = add nsw i64 %197, 15
  %199 = load %struct.arc** %arc, align 8
  %200 = getelementptr inbounds %struct.arc* %199, i32 0, i32 0
  store i64 %198, i64* %200, align 8
  %201 = load %struct.arc** %arc, align 8
  %202 = getelementptr inbounds %struct.arc* %201, i32 0, i32 0
  %203 = load i64* %202, align 8
  %204 = load %struct.arc** %arc, align 8
  %205 = getelementptr inbounds %struct.arc* %204, i32 0, i32 7
  store i64 %203, i64* %205, align 8
  %206 = load %struct.arc** %arc, align 8
  %207 = getelementptr inbounds %struct.arc* %206, i32 0, i32 1
  %208 = load %struct.node** %207, align 8
  %209 = getelementptr inbounds %struct.node* %208, i32 0, i32 7
  %210 = load %struct.arc** %209, align 8
  %211 = load %struct.arc** %arc, align 8
  %212 = getelementptr inbounds %struct.arc* %211, i32 0, i32 4
  store %struct.arc* %210, %struct.arc** %212, align 8
  %213 = load %struct.arc** %arc, align 8
  %214 = getelementptr inbounds %struct.arc* %213, i32 0, i32 1
  %215 = load %struct.node** %214, align 8
  %216 = getelementptr inbounds %struct.node* %215, i32 0, i32 7
  %217 = load %struct.arc** %arc, align 8
  store %struct.arc* %217, %struct.arc** %216, align 8
  %218 = load %struct.arc** %arc, align 8
  %219 = getelementptr inbounds %struct.arc* %218, i32 0, i32 2
  %220 = load %struct.node** %219, align 8
  %221 = getelementptr inbounds %struct.node* %220, i32 0, i32 8
  %222 = load %struct.arc** %221, align 8
  %223 = load %struct.arc** %arc, align 8
  %224 = getelementptr inbounds %struct.arc* %223, i32 0, i32 5
  store %struct.arc* %222, %struct.arc** %224, align 8
  %225 = load %struct.arc** %arc, align 8
  %226 = getelementptr inbounds %struct.arc* %225, i32 0, i32 2
  %227 = load %struct.node** %226, align 8
  %228 = getelementptr inbounds %struct.node* %227, i32 0, i32 8
  %229 = load %struct.arc** %arc, align 8
  store %struct.arc* %229, %struct.arc** %228, align 8
  %230 = load %struct.arc** %arc, align 8
  %231 = getelementptr inbounds %struct.arc* %230, i64 1
  store %struct.arc* %231, %struct.arc** %arc, align 8
  %232 = load %struct.network_t** %net_addr, align 8
  %233 = getelementptr inbounds %struct.network_t* %232, i32 0, i32 3
  %234 = load i64* %233, align 8
  %235 = load i64* %i, align 8
  %236 = add nsw i64 %234, %235
  %237 = load %struct.node** %node, align 8
  %238 = getelementptr inbounds %struct.node* %237, i64 %236
  %239 = load %struct.arc** %arc, align 8
  %240 = getelementptr inbounds %struct.arc* %239, i32 0, i32 1
  store %struct.node* %238, %struct.node** %240, align 8
  %241 = load %struct.network_t** %net_addr, align 8
  %242 = getelementptr inbounds %struct.network_t* %241, i32 0, i32 2
  %243 = load i64* %242, align 8
  %244 = load %struct.node** %node, align 8
  %245 = getelementptr inbounds %struct.node* %244, i64 %243
  %246 = load %struct.arc** %arc, align 8
  %247 = getelementptr inbounds %struct.arc* %246, i32 0, i32 2
  store %struct.node* %245, %struct.node** %247, align 8
  %248 = load %struct.arc** %arc, align 8
  %249 = getelementptr inbounds %struct.arc* %248, i32 0, i32 0
  store i64 15, i64* %249, align 8
  %250 = load %struct.arc** %arc, align 8
  %251 = getelementptr inbounds %struct.arc* %250, i32 0, i32 0
  %252 = load i64* %251, align 8
  %253 = load %struct.arc** %arc, align 8
  %254 = getelementptr inbounds %struct.arc* %253, i32 0, i32 7
  store i64 %252, i64* %254, align 8
  %255 = load %struct.arc** %arc, align 8
  %256 = getelementptr inbounds %struct.arc* %255, i32 0, i32 1
  %257 = load %struct.node** %256, align 8
  %258 = getelementptr inbounds %struct.node* %257, i32 0, i32 7
  %259 = load %struct.arc** %258, align 8
  %260 = load %struct.arc** %arc, align 8
  %261 = getelementptr inbounds %struct.arc* %260, i32 0, i32 4
  store %struct.arc* %259, %struct.arc** %261, align 8
  %262 = load %struct.arc** %arc, align 8
  %263 = getelementptr inbounds %struct.arc* %262, i32 0, i32 1
  %264 = load %struct.node** %263, align 8
  %265 = getelementptr inbounds %struct.node* %264, i32 0, i32 7
  %266 = load %struct.arc** %arc, align 8
  store %struct.arc* %266, %struct.arc** %265, align 8
  %267 = load %struct.arc** %arc, align 8
  %268 = getelementptr inbounds %struct.arc* %267, i32 0, i32 2
  %269 = load %struct.node** %268, align 8
  %270 = getelementptr inbounds %struct.node* %269, i32 0, i32 8
  %271 = load %struct.arc** %270, align 8
  %272 = load %struct.arc** %arc, align 8
  %273 = getelementptr inbounds %struct.arc* %272, i32 0, i32 5
  store %struct.arc* %271, %struct.arc** %273, align 8
  %274 = load %struct.arc** %arc, align 8
  %275 = getelementptr inbounds %struct.arc* %274, i32 0, i32 2
  %276 = load %struct.node** %275, align 8
  %277 = getelementptr inbounds %struct.node* %276, i32 0, i32 8
  %278 = load %struct.arc** %arc, align 8
  store %struct.arc* %278, %struct.arc** %277, align 8
  %279 = load %struct.arc** %arc, align 8
  %280 = getelementptr inbounds %struct.arc* %279, i64 1
  store %struct.arc* %280, %struct.arc** %arc, align 8
  %281 = load %struct.node** %node, align 8
  %282 = load i64* %i, align 8
  %283 = getelementptr inbounds %struct.node* %281, i64 %282
  %284 = load %struct.arc** %arc, align 8
  %285 = getelementptr inbounds %struct.arc* %284, i32 0, i32 1
  store %struct.node* %283, %struct.node** %285, align 8
  %286 = load %struct.network_t** %net_addr, align 8
  %287 = getelementptr inbounds %struct.network_t* %286, i32 0, i32 3
  %288 = load i64* %287, align 8
  %289 = load i64* %i, align 8
  %290 = add nsw i64 %288, %289
  %291 = load %struct.node** %node, align 8
  %292 = getelementptr inbounds %struct.node* %291, i64 %290
  %293 = load %struct.arc** %arc, align 8
  %294 = getelementptr inbounds %struct.arc* %293, i32 0, i32 2
  store %struct.node* %292, %struct.node** %294, align 8
  %295 = load %struct.network_t** %net_addr, align 8
  %296 = getelementptr inbounds %struct.network_t* %295, i32 0, i32 18
  %297 = load i64* %296, align 8
  %298 = icmp sge i64 %297, 10000000
  %max = select i1 %298, i64 %297, i64 10000000
  %299 = mul nsw i64 %max, 2
  %300 = load %struct.arc** %arc, align 8
  %301 = getelementptr inbounds %struct.arc* %300, i32 0, i32 0
  store i64 %299, i64* %301, align 8
  %302 = load %struct.arc** %arc, align 8
  %303 = getelementptr inbounds %struct.arc* %302, i32 0, i32 0
  %304 = load i64* %303, align 8
  %305 = load %struct.arc** %arc, align 8
  %306 = getelementptr inbounds %struct.arc* %305, i32 0, i32 7
  store i64 %304, i64* %306, align 8
  %307 = load %struct.arc** %arc, align 8
  %308 = getelementptr inbounds %struct.arc* %307, i32 0, i32 1
  %309 = load %struct.node** %308, align 8
  %310 = getelementptr inbounds %struct.node* %309, i32 0, i32 7
  %311 = load %struct.arc** %310, align 8
  %312 = load %struct.arc** %arc, align 8
  %313 = getelementptr inbounds %struct.arc* %312, i32 0, i32 4
  store %struct.arc* %311, %struct.arc** %313, align 8
  %314 = load %struct.arc** %arc, align 8
  %315 = getelementptr inbounds %struct.arc* %314, i32 0, i32 1
  %316 = load %struct.node** %315, align 8
  %317 = getelementptr inbounds %struct.node* %316, i32 0, i32 7
  %318 = load %struct.arc** %arc, align 8
  store %struct.arc* %318, %struct.arc** %317, align 8
  %319 = load %struct.arc** %arc, align 8
  %320 = getelementptr inbounds %struct.arc* %319, i32 0, i32 2
  %321 = load %struct.node** %320, align 8
  %322 = getelementptr inbounds %struct.node* %321, i32 0, i32 8
  %323 = load %struct.arc** %322, align 8
  %324 = load %struct.arc** %arc, align 8
  %325 = getelementptr inbounds %struct.arc* %324, i32 0, i32 5
  store %struct.arc* %323, %struct.arc** %325, align 8
  %326 = load %struct.arc** %arc, align 8
  %327 = getelementptr inbounds %struct.arc* %326, i32 0, i32 2
  %328 = load %struct.node** %327, align 8
  %329 = getelementptr inbounds %struct.node* %328, i32 0, i32 8
  %330 = load %struct.arc** %arc, align 8
  store %struct.arc* %330, %struct.arc** %329, align 8
  %331 = load %struct.arc** %arc, align 8
  %332 = getelementptr inbounds %struct.arc* %331, i64 1
  store %struct.arc* %332, %struct.arc** %arc, align 8
  %333 = load i64* %i, align 8
  %334 = add nsw i64 %333, 1
  store i64 %334, i64* %i, align 8
  br label %bb22

bb22:                                             ; preds = %bb20, %bb14
  %335 = load %struct.network_t** %net_addr, align 8
  %336 = getelementptr inbounds %struct.network_t* %335, i32 0, i32 3
  %337 = load i64* %336, align 8
  %338 = load i64* %i, align 8
  %339 = icmp sge i64 %337, %338
  br i1 %339, label %bb15, label %bb23

bb23:                                             ; preds = %bb22
  %340 = load %struct.network_t** %net_addr, align 8
  %341 = getelementptr inbounds %struct.network_t* %340, i32 0, i32 3
  %342 = load i64* %341, align 8
  %343 = add nsw i64 %342, 1
  %344 = load i64* %i, align 8
  %345 = icmp ne i64 %343, %344
  br i1 %345, label %bb24, label %bb25

bb24:                                             ; preds = %bb23
  store i64 -1, i64* %0, align 8
  br label %bb45

bb25:                                             ; preds = %bb23
  store i64 0, i64* %i, align 8
  br label %bb31

bb26:                                             ; preds = %bb31
  %instring27 = bitcast [201 x i8]* %instring to i8*
  %346 = load %struct.FILE** %in, align 8
  %347 = call i8* @fgets(i8* noalias %instring27, i32 200, %struct.FILE* noalias %346) nounwind
  %instring28 = bitcast [201 x i8]* %instring to i8*
  %348 = call i32 (i8*, i8*, ...)* @"\01__isoc99_sscanf"(i8* noalias %instring28, i8* noalias getelementptr inbounds ([12 x i8]* @.str535, i64 0, i64 0), i64* %t, i64* %h, i64* %c) nounwind
  %349 = icmp ne i32 %348, 3
  br i1 %349, label %bb29, label %bb30

bb29:                                             ; preds = %bb26
  store i64 -1, i64* %0, align 8
  br label %bb45

bb30:                                             ; preds = %bb26
  %350 = load %struct.network_t** %net_addr, align 8
  %351 = getelementptr inbounds %struct.network_t* %350, i32 0, i32 3
  %352 = load i64* %351, align 8
  %353 = load i64* %t, align 8
  %354 = add nsw i64 %352, %353
  %355 = load %struct.node** %node, align 8
  %356 = getelementptr inbounds %struct.node* %355, i64 %354
  %357 = load %struct.arc** %arc, align 8
  %358 = getelementptr inbounds %struct.arc* %357, i32 0, i32 1
  store %struct.node* %356, %struct.node** %358, align 8
  %359 = load i64* %h, align 8
  %360 = load %struct.node** %node, align 8
  %361 = getelementptr inbounds %struct.node* %360, i64 %359
  %362 = load %struct.arc** %arc, align 8
  %363 = getelementptr inbounds %struct.arc* %362, i32 0, i32 2
  store %struct.node* %361, %struct.node** %363, align 8
  %364 = load i64* %c, align 8
  %365 = load %struct.arc** %arc, align 8
  %366 = getelementptr inbounds %struct.arc* %365, i32 0, i32 7
  store i64 %364, i64* %366, align 8
  %367 = load i64* %c, align 8
  %368 = load %struct.arc** %arc, align 8
  %369 = getelementptr inbounds %struct.arc* %368, i32 0, i32 0
  store i64 %367, i64* %369, align 8
  %370 = load %struct.arc** %arc, align 8
  %371 = getelementptr inbounds %struct.arc* %370, i32 0, i32 1
  %372 = load %struct.node** %371, align 8
  %373 = getelementptr inbounds %struct.node* %372, i32 0, i32 7
  %374 = load %struct.arc** %373, align 8
  %375 = load %struct.arc** %arc, align 8
  %376 = getelementptr inbounds %struct.arc* %375, i32 0, i32 4
  store %struct.arc* %374, %struct.arc** %376, align 8
  %377 = load %struct.arc** %arc, align 8
  %378 = getelementptr inbounds %struct.arc* %377, i32 0, i32 1
  %379 = load %struct.node** %378, align 8
  %380 = getelementptr inbounds %struct.node* %379, i32 0, i32 7
  %381 = load %struct.arc** %arc, align 8
  store %struct.arc* %381, %struct.arc** %380, align 8
  %382 = load %struct.arc** %arc, align 8
  %383 = getelementptr inbounds %struct.arc* %382, i32 0, i32 2
  %384 = load %struct.node** %383, align 8
  %385 = getelementptr inbounds %struct.node* %384, i32 0, i32 8
  %386 = load %struct.arc** %385, align 8
  %387 = load %struct.arc** %arc, align 8
  %388 = getelementptr inbounds %struct.arc* %387, i32 0, i32 5
  store %struct.arc* %386, %struct.arc** %388, align 8
  %389 = load %struct.arc** %arc, align 8
  %390 = getelementptr inbounds %struct.arc* %389, i32 0, i32 2
  %391 = load %struct.node** %390, align 8
  %392 = getelementptr inbounds %struct.node* %391, i32 0, i32 8
  %393 = load %struct.arc** %arc, align 8
  store %struct.arc* %393, %struct.arc** %392, align 8
  %394 = load i64* %i, align 8
  %395 = add nsw i64 %394, 1
  store i64 %395, i64* %i, align 8
  %396 = load %struct.arc** %arc, align 8
  %397 = getelementptr inbounds %struct.arc* %396, i64 1
  store %struct.arc* %397, %struct.arc** %arc, align 8
  br label %bb31

bb31:                                             ; preds = %bb30, %bb25
  %398 = load %struct.network_t** %net_addr, align 8
  %399 = getelementptr inbounds %struct.network_t* %398, i32 0, i32 6
  %400 = load i64* %399, align 8
  %401 = load i64* %i, align 8
  %402 = icmp sgt i64 %400, %401
  br i1 %402, label %bb26, label %bb32

bb32:                                             ; preds = %bb31
  %403 = load %struct.network_t** %net_addr, align 8
  %404 = getelementptr inbounds %struct.network_t* %403, i32 0, i32 24
  %405 = load %struct.arc** %404, align 8
  %406 = load %struct.arc** %arc, align 8
  %407 = icmp ne %struct.arc* %405, %406
  br i1 %407, label %bb33, label %bb37

bb33:                                             ; preds = %bb32
  %408 = load %struct.network_t** %net_addr, align 8
  %409 = getelementptr inbounds %struct.network_t* %408, i32 0, i32 24
  %410 = load %struct.arc** %arc, align 8
  store %struct.arc* %410, %struct.arc** %409, align 8
  %411 = load %struct.network_t** %net_addr, align 8
  %412 = getelementptr inbounds %struct.network_t* %411, i32 0, i32 23
  %413 = load %struct.arc** %412, align 8
  store %struct.arc* %413, %struct.arc** %arc, align 8
  %414 = load %struct.network_t** %net_addr, align 8
  %415 = getelementptr inbounds %struct.network_t* %414, i32 0, i32 5
  store i64 0, i64* %415, align 8
  br label %bb35

bb34:                                             ; preds = %bb35
  %416 = load %struct.network_t** %net_addr, align 8
  %417 = getelementptr inbounds %struct.network_t* %416, i32 0, i32 5
  %418 = load i64* %417, align 8
  %419 = add nsw i64 %418, 1
  %420 = load %struct.network_t** %net_addr, align 8
  %421 = getelementptr inbounds %struct.network_t* %420, i32 0, i32 5
  store i64 %419, i64* %421, align 8
  %422 = load %struct.arc** %arc, align 8
  %423 = getelementptr inbounds %struct.arc* %422, i64 1
  store %struct.arc* %423, %struct.arc** %arc, align 8
  br label %bb35

bb35:                                             ; preds = %bb34, %bb33
  %424 = load %struct.network_t** %net_addr, align 8
  %425 = getelementptr inbounds %struct.network_t* %424, i32 0, i32 24
  %426 = load %struct.arc** %425, align 8
  %427 = load %struct.arc** %arc, align 8
  %428 = icmp ugt %struct.arc* %426, %427
  br i1 %428, label %bb34, label %bb36

bb36:                                             ; preds = %bb35
  %429 = load %struct.network_t** %net_addr, align 8
  %430 = getelementptr inbounds %struct.network_t* %429, i32 0, i32 5
  %431 = load i64* %430, align 8
  %432 = load %struct.network_t** %net_addr, align 8
  %433 = getelementptr inbounds %struct.network_t* %432, i32 0, i32 6
  store i64 %431, i64* %433, align 8
  br label %bb37

bb37:                                             ; preds = %bb36, %bb32
  %434 = load %struct.FILE** %in, align 8
  %435 = call i32 @fclose(%struct.FILE* %434) nounwind
  %436 = load %struct.network_t** %net_addr, align 8
  %437 = getelementptr inbounds %struct.network_t* %436, i32 0, i32 1
  %438 = getelementptr inbounds [200 x i8]* %437, i64 0, i64 0
  store i8 0, i8* %438, align 1
  store i64 1, i64* %i, align 8
  br label %bb43

bb38:                                             ; preds = %bb43
  %439 = load %struct.network_t** %net_addr, align 8
  %440 = getelementptr inbounds %struct.network_t* %439, i32 0, i32 23
  %441 = load %struct.arc** %440, align 8
  %442 = load i64* %i, align 8
  %443 = mul nsw i64 %442, 3
  %444 = sub nsw i64 %443, 1
  %445 = getelementptr inbounds %struct.arc* %441, i64 %444
  %446 = load %struct.network_t** %net_addr, align 8
  %447 = getelementptr inbounds %struct.network_t* %446, i32 0, i32 18
  %448 = load i64* %447, align 8
  %449 = icmp sge i64 %448, 10000000
  %max39 = select i1 %449, i64 %448, i64 10000000
  %450 = mul nsw i64 %max39, -2
  %451 = getelementptr inbounds %struct.arc* %445, i32 0, i32 0
  store i64 %450, i64* %451, align 8
  %452 = load %struct.network_t** %net_addr, align 8
  %453 = getelementptr inbounds %struct.network_t* %452, i32 0, i32 23
  %454 = load %struct.arc** %453, align 8
  %455 = load i64* %i, align 8
  %456 = mul nsw i64 %455, 3
  %457 = sub nsw i64 %456, 1
  %458 = getelementptr inbounds %struct.arc* %454, i64 %457
  %459 = load %struct.network_t** %net_addr, align 8
  %460 = getelementptr inbounds %struct.network_t* %459, i32 0, i32 18
  %461 = load i64* %460, align 8
  %462 = icmp sge i64 %461, 10000000
  %max41 = select i1 %462, i64 %461, i64 10000000
  %463 = mul nsw i64 %max41, -2
  %464 = getelementptr inbounds %struct.arc* %458, i32 0, i32 7
  store i64 %463, i64* %464, align 8
  %465 = load i64* %i, align 8
  %466 = add nsw i64 %465, 1
  store i64 %466, i64* %i, align 8
  br label %bb43

bb43:                                             ; preds = %bb38, %bb37
  %467 = load %struct.network_t** %net_addr, align 8
  %468 = getelementptr inbounds %struct.network_t* %467, i32 0, i32 3
  %469 = load i64* %468, align 8
  %470 = load i64* %i, align 8
  %471 = icmp sge i64 %469, %470
  br i1 %471, label %bb38, label %bb44

bb44:                                             ; preds = %bb43
  store i64 0, i64* %0, align 8
  br label %bb45

bb45:                                             ; preds = %bb44, %bb29, %bb24, %bb19, %bb13, %bb4, %bb
  %472 = load i64* %0, align 8
  store i64 %472, i64* %retval, align 8
  br label %return

return:                                           ; preds = %bb45
  %retval46 = load i64* %retval
  ret i64 %retval46
}

declare i8* @fgets(i8* noalias, i32, %struct.FILE* noalias)

declare i32 @"\01__isoc99_sscanf"(i8* noalias, i8* noalias, ...) nounwind

declare noalias i8* @calloc(i64, i64) nounwind

define void @update_tree(i64 %cycle_ori, i64 %new_orientation, i64 %delta, i64 %new_flow, %struct.node* %iplus, %struct.node* %jplus, %struct.node* %iminus, %struct.node* %jminus, %struct.node* %w, %struct.arc* %bea, i64 %sigma, i64 %feas_tol) nounwind {
entry:
  %cycle_ori_addr = alloca i64, align 8
  %new_orientation_addr = alloca i64, align 8
  %delta_addr = alloca i64, align 8
  %new_flow_addr = alloca i64, align 8
  %iplus_addr = alloca %struct.node*, align 8
  %jplus_addr = alloca %struct.node*, align 8
  %iminus_addr = alloca %struct.node*, align 8
  %jminus_addr = alloca %struct.node*, align 8
  %w_addr = alloca %struct.node*, align 8
  %bea_addr = alloca %struct.arc*, align 8
  %sigma_addr = alloca i64, align 8
  %feas_tol_addr = alloca i64, align 8
  %basic_arc_temp = alloca %struct.arc*
  %new_basic_arc = alloca %struct.arc*
  %father = alloca %struct.node*
  %temp = alloca %struct.node*
  %new_pred = alloca %struct.node*
  %orientation_temp = alloca i64
  %depth_temp = alloca i64
  %depth_iminus = alloca i64
  %new_depth = alloca i64
  %flow_temp = alloca i64
  %"alloca point" = bitcast i32 0 to i32
  store i64 %cycle_ori, i64* %cycle_ori_addr
  store i64 %new_orientation, i64* %new_orientation_addr
  store i64 %delta, i64* %delta_addr
  store i64 %new_flow, i64* %new_flow_addr
  store %struct.node* %iplus, %struct.node** %iplus_addr
  store %struct.node* %jplus, %struct.node** %jplus_addr
  store %struct.node* %iminus, %struct.node** %iminus_addr
  store %struct.node* %jminus, %struct.node** %jminus_addr
  store %struct.node* %w, %struct.node** %w_addr
  store %struct.arc* %bea, %struct.arc** %bea_addr
  store i64 %sigma, i64* %sigma_addr
  store i64 %feas_tol, i64* %feas_tol_addr
  %0 = load %struct.arc** %bea_addr, align 8
  %1 = getelementptr inbounds %struct.arc* %0, i32 0, i32 1
  %2 = load %struct.node** %1, align 8
  %3 = load %struct.node** %jplus_addr, align 8
  %4 = icmp ne %struct.node* %2, %3
  br i1 %4, label %bb1, label %bb

bb:                                               ; preds = %entry
  %5 = load i64* %sigma_addr, align 8
  %6 = icmp slt i64 %5, 0
  br i1 %6, label %bb3, label %bb1

bb1:                                              ; preds = %bb, %entry
  %7 = load %struct.arc** %bea_addr, align 8
  %8 = getelementptr inbounds %struct.arc* %7, i32 0, i32 1
  %9 = load %struct.node** %8, align 8
  %10 = load %struct.node** %iplus_addr, align 8
  %11 = icmp ne %struct.node* %9, %10
  br i1 %11, label %bb4, label %bb2

bb2:                                              ; preds = %bb1
  %12 = load i64* %sigma_addr, align 8
  %13 = icmp sgt i64 %12, 0
  br i1 %13, label %bb3, label %bb4

bb3:                                              ; preds = %bb2, %bb
  %14 = load i64* %sigma_addr, align 8
  %neg = sub i64 0, %14
  %abscond = icmp sge i64 %14, 0
  %abs = select i1 %abscond, i64 %14, i64 %neg
  store i64 %abs, i64* %sigma_addr, align 8
  br label %bb9

bb4:                                              ; preds = %bb2, %bb1
  %15 = load i64* %sigma_addr, align 8
  %neg5 = sub i64 0, %15
  %abscond6 = icmp sge i64 %15, 0
  %abs7 = select i1 %abscond6, i64 %15, i64 %neg5
  %16 = sub nsw i64 0, %abs7
  store i64 %16, i64* %sigma_addr, align 8
  br label %bb9

bb9:                                              ; preds = %bb4, %bb3
  %17 = load %struct.node** %iminus_addr, align 8
  store %struct.node* %17, %struct.node** %father, align 8
  %18 = load %struct.node** %father, align 8
  %19 = getelementptr inbounds %struct.node* %18, i32 0, i32 0
  %20 = load i64* %19, align 8
  %21 = load i64* %sigma_addr, align 8
  %22 = add nsw i64 %20, %21
  %23 = load %struct.node** %father, align 8
  %24 = getelementptr inbounds %struct.node* %23, i32 0, i32 0
  store i64 %22, i64* %24, align 8
  br label %RECURSION

RECURSION:                                        ; preds = %ITERATION, %bb9
  %25 = load %struct.node** %father, align 8
  %26 = getelementptr inbounds %struct.node* %25, i32 0, i32 2
  %27 = load %struct.node** %26, align 8
  store %struct.node* %27, %struct.node** %temp, align 8
  %28 = load %struct.node** %temp, align 8
  %29 = icmp ne %struct.node* %28, null
  br i1 %29, label %ITERATION, label %TEST

ITERATION:                                        ; preds = %bb10, %RECURSION
  %30 = load %struct.node** %temp, align 8
  %31 = getelementptr inbounds %struct.node* %30, i32 0, i32 0
  %32 = load i64* %31, align 8
  %33 = load i64* %sigma_addr, align 8
  %34 = add nsw i64 %32, %33
  %35 = load %struct.node** %temp, align 8
  %36 = getelementptr inbounds %struct.node* %35, i32 0, i32 0
  store i64 %34, i64* %36, align 8
  %37 = load %struct.node** %temp, align 8
  store %struct.node* %37, %struct.node** %father, align 8
  br label %RECURSION

TEST:                                             ; preds = %bb11, %RECURSION
  %38 = load %struct.node** %father, align 8
  %39 = load %struct.node** %iminus_addr, align 8
  %40 = icmp eq %struct.node* %38, %39
  br i1 %40, label %CONTINUE, label %bb10

bb10:                                             ; preds = %TEST
  %41 = load %struct.node** %father, align 8
  %42 = getelementptr inbounds %struct.node* %41, i32 0, i32 4
  %43 = load %struct.node** %42, align 8
  store %struct.node* %43, %struct.node** %temp, align 8
  %44 = load %struct.node** %temp, align 8
  %45 = icmp ne %struct.node* %44, null
  br i1 %45, label %ITERATION, label %bb11

bb11:                                             ; preds = %bb10
  %46 = load %struct.node** %father, align 8
  %47 = getelementptr inbounds %struct.node* %46, i32 0, i32 3
  %48 = load %struct.node** %47, align 8
  store %struct.node* %48, %struct.node** %father, align 8
  br label %TEST

CONTINUE:                                         ; preds = %TEST
  %49 = load %struct.node** %iplus_addr, align 8
  store %struct.node* %49, %struct.node** %temp, align 8
  %50 = load %struct.node** %temp, align 8
  %51 = getelementptr inbounds %struct.node* %50, i32 0, i32 3
  %52 = load %struct.node** %51, align 8
  store %struct.node* %52, %struct.node** %father, align 8
  %53 = load %struct.node** %iminus_addr, align 8
  %54 = getelementptr inbounds %struct.node* %53, i32 0, i32 11
  %55 = load i64* %54, align 8
  store i64 %55, i64* %depth_iminus, align 8
  %56 = load i64* %depth_iminus, align 8
  store i64 %56, i64* %new_depth, align 8
  %57 = load %struct.node** %jplus_addr, align 8
  store %struct.node* %57, %struct.node** %new_pred, align 8
  %58 = load %struct.arc** %bea_addr, align 8
  store %struct.arc* %58, %struct.arc** %new_basic_arc, align 8
  br label %bb23

bb12:                                             ; preds = %bb23
  %59 = load %struct.node** %temp, align 8
  %60 = getelementptr inbounds %struct.node* %59, i32 0, i32 4
  %61 = load %struct.node** %60, align 8
  %62 = icmp ne %struct.node* %61, null
  br i1 %62, label %bb13, label %bb14

bb13:                                             ; preds = %bb12
  %63 = load %struct.node** %temp, align 8
  %64 = getelementptr inbounds %struct.node* %63, i32 0, i32 4
  %65 = load %struct.node** %64, align 8
  %66 = load %struct.node** %temp, align 8
  %67 = getelementptr inbounds %struct.node* %66, i32 0, i32 5
  %68 = load %struct.node** %67, align 8
  %69 = getelementptr inbounds %struct.node* %65, i32 0, i32 5
  store %struct.node* %68, %struct.node** %69, align 8
  br label %bb14

bb14:                                             ; preds = %bb13, %bb12
  %70 = load %struct.node** %temp, align 8
  %71 = getelementptr inbounds %struct.node* %70, i32 0, i32 5
  %72 = load %struct.node** %71, align 8
  %73 = icmp ne %struct.node* %72, null
  br i1 %73, label %bb15, label %bb16

bb15:                                             ; preds = %bb14
  %74 = load %struct.node** %temp, align 8
  %75 = getelementptr inbounds %struct.node* %74, i32 0, i32 5
  %76 = load %struct.node** %75, align 8
  %77 = load %struct.node** %temp, align 8
  %78 = getelementptr inbounds %struct.node* %77, i32 0, i32 4
  %79 = load %struct.node** %78, align 8
  %80 = getelementptr inbounds %struct.node* %76, i32 0, i32 4
  store %struct.node* %79, %struct.node** %80, align 8
  br label %bb17

bb16:                                             ; preds = %bb14
  %81 = load %struct.node** %temp, align 8
  %82 = getelementptr inbounds %struct.node* %81, i32 0, i32 4
  %83 = load %struct.node** %82, align 8
  %84 = load %struct.node** %father, align 8
  %85 = getelementptr inbounds %struct.node* %84, i32 0, i32 2
  store %struct.node* %83, %struct.node** %85, align 8
  br label %bb17

bb17:                                             ; preds = %bb16, %bb15
  %86 = load %struct.node** %temp, align 8
  %87 = getelementptr inbounds %struct.node* %86, i32 0, i32 3
  %88 = load %struct.node** %new_pred, align 8
  store %struct.node* %88, %struct.node** %87, align 8
  %89 = load %struct.node** %new_pred, align 8
  %90 = getelementptr inbounds %struct.node* %89, i32 0, i32 2
  %91 = load %struct.node** %90, align 8
  %92 = load %struct.node** %temp, align 8
  %93 = getelementptr inbounds %struct.node* %92, i32 0, i32 4
  store %struct.node* %91, %struct.node** %93, align 8
  %94 = load %struct.node** %temp, align 8
  %95 = getelementptr inbounds %struct.node* %94, i32 0, i32 4
  %96 = load %struct.node** %95, align 8
  %97 = icmp ne %struct.node* %96, null
  br i1 %97, label %bb18, label %bb19

bb18:                                             ; preds = %bb17
  %98 = load %struct.node** %temp, align 8
  %99 = getelementptr inbounds %struct.node* %98, i32 0, i32 4
  %100 = load %struct.node** %99, align 8
  %101 = getelementptr inbounds %struct.node* %100, i32 0, i32 5
  %102 = load %struct.node** %temp, align 8
  store %struct.node* %102, %struct.node** %101, align 8
  br label %bb19

bb19:                                             ; preds = %bb18, %bb17
  %103 = load %struct.node** %new_pred, align 8
  %104 = getelementptr inbounds %struct.node* %103, i32 0, i32 2
  %105 = load %struct.node** %temp, align 8
  store %struct.node* %105, %struct.node** %104, align 8
  %106 = load %struct.node** %temp, align 8
  %107 = getelementptr inbounds %struct.node* %106, i32 0, i32 5
  store %struct.node* null, %struct.node** %107, align 8
  %108 = load %struct.node** %temp, align 8
  %109 = getelementptr inbounds %struct.node* %108, i32 0, i32 1
  %110 = load i32* %109, align 8
  %111 = icmp eq i32 %110, 0
  %112 = zext i1 %111 to i64
  store i64 %112, i64* %orientation_temp, align 8
  %113 = load i64* %orientation_temp, align 8
  %114 = load i64* %cycle_ori_addr, align 8
  %115 = icmp eq i64 %113, %114
  br i1 %115, label %bb20, label %bb21

bb20:                                             ; preds = %bb19
  %116 = load %struct.node** %temp, align 8
  %117 = getelementptr inbounds %struct.node* %116, i32 0, i32 10
  %118 = load i64* %117, align 8
  %119 = load i64* %delta_addr, align 8
  %120 = add nsw i64 %118, %119
  store i64 %120, i64* %flow_temp, align 8
  br label %bb22

bb21:                                             ; preds = %bb19
  %121 = load %struct.node** %temp, align 8
  %122 = getelementptr inbounds %struct.node* %121, i32 0, i32 10
  %123 = load i64* %122, align 8
  %124 = load i64* %delta_addr, align 8
  %125 = sub nsw i64 %123, %124
  store i64 %125, i64* %flow_temp, align 8
  br label %bb22

bb22:                                             ; preds = %bb21, %bb20
  %126 = load %struct.node** %temp, align 8
  %127 = getelementptr inbounds %struct.node* %126, i32 0, i32 6
  %128 = load %struct.arc** %127, align 8
  store %struct.arc* %128, %struct.arc** %basic_arc_temp, align 8
  %129 = load %struct.node** %temp, align 8
  %130 = getelementptr inbounds %struct.node* %129, i32 0, i32 11
  %131 = load i64* %130, align 8
  store i64 %131, i64* %depth_temp, align 8
  %132 = load i64* %new_orientation_addr, align 8
  %133 = trunc i64 %132 to i32
  %134 = load %struct.node** %temp, align 8
  %135 = getelementptr inbounds %struct.node* %134, i32 0, i32 1
  store i32 %133, i32* %135, align 8
  %136 = load %struct.node** %temp, align 8
  %137 = getelementptr inbounds %struct.node* %136, i32 0, i32 10
  %138 = load i64* %new_flow_addr, align 8
  store i64 %138, i64* %137, align 8
  %139 = load %struct.node** %temp, align 8
  %140 = getelementptr inbounds %struct.node* %139, i32 0, i32 6
  %141 = load %struct.arc** %new_basic_arc, align 8
  store %struct.arc* %141, %struct.arc** %140, align 8
  %142 = load %struct.node** %temp, align 8
  %143 = getelementptr inbounds %struct.node* %142, i32 0, i32 11
  %144 = load i64* %new_depth, align 8
  store i64 %144, i64* %143, align 8
  %145 = load %struct.node** %temp, align 8
  store %struct.node* %145, %struct.node** %new_pred, align 8
  %146 = load i64* %orientation_temp, align 8
  store i64 %146, i64* %new_orientation_addr, align 8
  %147 = load i64* %flow_temp, align 8
  store i64 %147, i64* %new_flow_addr, align 8
  %148 = load %struct.arc** %basic_arc_temp, align 8
  store %struct.arc* %148, %struct.arc** %new_basic_arc, align 8
  %149 = load i64* %depth_iminus, align 8
  %150 = load i64* %depth_temp, align 8
  %151 = sub nsw i64 %149, %150
  store i64 %151, i64* %new_depth, align 8
  %152 = load %struct.node** %father, align 8
  store %struct.node* %152, %struct.node** %temp, align 8
  %153 = load %struct.node** %temp, align 8
  %154 = getelementptr inbounds %struct.node* %153, i32 0, i32 3
  %155 = load %struct.node** %154, align 8
  store %struct.node* %155, %struct.node** %father, align 8
  br label %bb23

bb23:                                             ; preds = %bb22, %CONTINUE
  %156 = load %struct.node** %temp, align 8
  %157 = load %struct.node** %jminus_addr, align 8
  %158 = icmp ne %struct.node* %156, %157
  br i1 %158, label %bb12, label %bb24

bb24:                                             ; preds = %bb23
  %159 = load i64* %delta_addr, align 8
  %160 = load i64* %feas_tol_addr, align 8
  %161 = icmp sgt i64 %159, %160
  br i1 %161, label %bb25, label %bb38

bb25:                                             ; preds = %bb24
  %162 = load %struct.node** %jminus_addr, align 8
  store %struct.node* %162, %struct.node** %temp, align 8
  br label %bb30

bb26:                                             ; preds = %bb30
  %163 = load %struct.node** %temp, align 8
  %164 = getelementptr inbounds %struct.node* %163, i32 0, i32 11
  %165 = load i64* %164, align 8
  %166 = load i64* %depth_iminus, align 8
  %167 = sub nsw i64 %165, %166
  %168 = load %struct.node** %temp, align 8
  %169 = getelementptr inbounds %struct.node* %168, i32 0, i32 11
  store i64 %167, i64* %169, align 8
  %170 = load %struct.node** %temp, align 8
  %171 = getelementptr inbounds %struct.node* %170, i32 0, i32 1
  %172 = load i32* %171, align 8
  %173 = sext i32 %172 to i64
  %174 = load i64* %cycle_ori_addr, align 8
  %175 = icmp ne i64 %173, %174
  br i1 %175, label %bb27, label %bb28

bb27:                                             ; preds = %bb26
  %176 = load %struct.node** %temp, align 8
  %177 = getelementptr inbounds %struct.node* %176, i32 0, i32 10
  %178 = load i64* %177, align 8
  %179 = load i64* %delta_addr, align 8
  %180 = add nsw i64 %178, %179
  %181 = load %struct.node** %temp, align 8
  %182 = getelementptr inbounds %struct.node* %181, i32 0, i32 10
  store i64 %180, i64* %182, align 8
  br label %bb29

bb28:                                             ; preds = %bb26
  %183 = load %struct.node** %temp, align 8
  %184 = getelementptr inbounds %struct.node* %183, i32 0, i32 10
  %185 = load i64* %184, align 8
  %186 = load i64* %delta_addr, align 8
  %187 = sub nsw i64 %185, %186
  %188 = load %struct.node** %temp, align 8
  %189 = getelementptr inbounds %struct.node* %188, i32 0, i32 10
  store i64 %187, i64* %189, align 8
  br label %bb29

bb29:                                             ; preds = %bb28, %bb27
  %190 = load %struct.node** %temp, align 8
  %191 = getelementptr inbounds %struct.node* %190, i32 0, i32 3
  %192 = load %struct.node** %191, align 8
  store %struct.node* %192, %struct.node** %temp, align 8
  br label %bb30

bb30:                                             ; preds = %bb29, %bb25
  %193 = load %struct.node** %temp, align 8
  %194 = load %struct.node** %w_addr, align 8
  %195 = icmp ne %struct.node* %193, %194
  br i1 %195, label %bb26, label %bb31

bb31:                                             ; preds = %bb30
  %196 = load %struct.node** %jplus_addr, align 8
  store %struct.node* %196, %struct.node** %temp, align 8
  br label %bb36

bb32:                                             ; preds = %bb36
  %197 = load %struct.node** %temp, align 8
  %198 = getelementptr inbounds %struct.node* %197, i32 0, i32 11
  %199 = load i64* %198, align 8
  %200 = load i64* %depth_iminus, align 8
  %201 = add nsw i64 %199, %200
  %202 = load %struct.node** %temp, align 8
  %203 = getelementptr inbounds %struct.node* %202, i32 0, i32 11
  store i64 %201, i64* %203, align 8
  %204 = load %struct.node** %temp, align 8
  %205 = getelementptr inbounds %struct.node* %204, i32 0, i32 1
  %206 = load i32* %205, align 8
  %207 = sext i32 %206 to i64
  %208 = load i64* %cycle_ori_addr, align 8
  %209 = icmp eq i64 %207, %208
  br i1 %209, label %bb33, label %bb34

bb33:                                             ; preds = %bb32
  %210 = load %struct.node** %temp, align 8
  %211 = getelementptr inbounds %struct.node* %210, i32 0, i32 10
  %212 = load i64* %211, align 8
  %213 = load i64* %delta_addr, align 8
  %214 = add nsw i64 %212, %213
  %215 = load %struct.node** %temp, align 8
  %216 = getelementptr inbounds %struct.node* %215, i32 0, i32 10
  store i64 %214, i64* %216, align 8
  br label %bb35

bb34:                                             ; preds = %bb32
  %217 = load %struct.node** %temp, align 8
  %218 = getelementptr inbounds %struct.node* %217, i32 0, i32 10
  %219 = load i64* %218, align 8
  %220 = load i64* %delta_addr, align 8
  %221 = sub nsw i64 %219, %220
  %222 = load %struct.node** %temp, align 8
  %223 = getelementptr inbounds %struct.node* %222, i32 0, i32 10
  store i64 %221, i64* %223, align 8
  br label %bb35

bb35:                                             ; preds = %bb34, %bb33
  %224 = load %struct.node** %temp, align 8
  %225 = getelementptr inbounds %struct.node* %224, i32 0, i32 3
  %226 = load %struct.node** %225, align 8
  store %struct.node* %226, %struct.node** %temp, align 8
  br label %bb36

bb36:                                             ; preds = %bb35, %bb31
  %227 = load %struct.node** %temp, align 8
  %228 = load %struct.node** %w_addr, align 8
  %229 = icmp ne %struct.node* %227, %228
  br i1 %229, label %bb32, label %bb37

bb37:                                             ; preds = %bb36
  br label %bb44

bb38:                                             ; preds = %bb24
  %230 = load %struct.node** %jminus_addr, align 8
  store %struct.node* %230, %struct.node** %temp, align 8
  br label %bb40

bb39:                                             ; preds = %bb40
  %231 = load %struct.node** %temp, align 8
  %232 = getelementptr inbounds %struct.node* %231, i32 0, i32 11
  %233 = load i64* %232, align 8
  %234 = load i64* %depth_iminus, align 8
  %235 = sub nsw i64 %233, %234
  %236 = load %struct.node** %temp, align 8
  %237 = getelementptr inbounds %struct.node* %236, i32 0, i32 11
  store i64 %235, i64* %237, align 8
  %238 = load %struct.node** %temp, align 8
  %239 = getelementptr inbounds %struct.node* %238, i32 0, i32 3
  %240 = load %struct.node** %239, align 8
  store %struct.node* %240, %struct.node** %temp, align 8
  br label %bb40

bb40:                                             ; preds = %bb39, %bb38
  %241 = load %struct.node** %temp, align 8
  %242 = load %struct.node** %w_addr, align 8
  %243 = icmp ne %struct.node* %241, %242
  br i1 %243, label %bb39, label %bb41

bb41:                                             ; preds = %bb40
  %244 = load %struct.node** %jplus_addr, align 8
  store %struct.node* %244, %struct.node** %temp, align 8
  br label %bb43

bb42:                                             ; preds = %bb43
  %245 = load %struct.node** %temp, align 8
  %246 = getelementptr inbounds %struct.node* %245, i32 0, i32 11
  %247 = load i64* %246, align 8
  %248 = load i64* %depth_iminus, align 8
  %249 = add nsw i64 %247, %248
  %250 = load %struct.node** %temp, align 8
  %251 = getelementptr inbounds %struct.node* %250, i32 0, i32 11
  store i64 %249, i64* %251, align 8
  %252 = load %struct.node** %temp, align 8
  %253 = getelementptr inbounds %struct.node* %252, i32 0, i32 3
  %254 = load %struct.node** %253, align 8
  store %struct.node* %254, %struct.node** %temp, align 8
  br label %bb43

bb43:                                             ; preds = %bb42, %bb41
  %255 = load %struct.node** %temp, align 8
  %256 = load %struct.node** %w_addr, align 8
  %257 = icmp ne %struct.node* %255, %256
  br i1 %257, label %bb42, label %bb44

bb44:                                             ; preds = %bb43, %bb37
  br label %return

return:                                           ; preds = %bb44
  ret void
}
