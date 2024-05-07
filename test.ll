; ModuleID = 'test.c'
source_filename = "test.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-redhat-linux-gnu"

@.str = private unnamed_addr constant [20 x i8] c"Salto 1.1.1, z = %d\00", align 1
@.str.2 = private unnamed_addr constant [18 x i8] c"Salto 1.1, a = %d\00", align 1
@.str.3 = private unnamed_addr constant [18 x i8] c"Salto 1.2, a = %d\00", align 1
@.str.4 = private unnamed_addr constant [18 x i8] c"Salto 2.1, a = %d\00", align 1
@.str.5 = private unnamed_addr constant [18 x i8] c"Salto 2.2, a = %d\00", align 1
@.str.6 = private unnamed_addr constant [17 x i8] c"Hello, World! %d\00", align 1

; Function Attrs: nofree nounwind uwtable
define dso_local i32 @main(i32 noundef %0, ptr nocapture noundef readnone %1) local_unnamed_addr #0 {
  %3 = icmp eq i32 %0, 0
  br i1 %3, label %4, label %7

4:                                                ; preds = %2
  %5 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str, i32 noundef 17)
  %6 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.2, i32 noundef 15)
  br label %10

7:                                                ; preds = %2
  %8 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.3, i32 noundef 11)
  %9 = add nsw i32 %0, 4
  br label %10

10:                                               ; preds = %7, %4
  %11 = phi i32 [ 16, %4 ], [ 12, %7 ]
  %12 = phi i32 [ 18, %4 ], [ %9, %7 ]
  %13 = add nsw i32 %12, %11
  %14 = icmp eq i32 %13, 7
  br i1 %14, label %15, label %17

15:                                               ; preds = %10
  %16 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.4, i32 noundef 15)
  br label %20

17:                                               ; preds = %10
  %18 = or i32 %11, 1
  %19 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.5, i32 noundef %18)
  br label %20

20:                                               ; preds = %17, %15
  %21 = phi i32 [ 15, %15 ], [ %18, %17 ]
  %22 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.6, i32 noundef %21)
  ret i32 0
}

; Function Attrs: nofree nounwind
declare dso_local noundef i32 @printf(ptr nocapture noundef readonly, ...) local_unnamed_addr #1

attributes #0 = { nofree nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"uwtable", i32 2}
!2 = !{!"clang version 16.0.6 (Red Hat 16.0.6-1.el9)"}
