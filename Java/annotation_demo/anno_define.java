package com.fanggang.annotation;
 
import java.lang.annotation.ElementType;
import java.lang.annotation.Target;

/**
 * 定义注解 Test 
 * 首先使用ElementType.TYPE
 * 运行级别定为 运行时，以便后面测试解析
 */ 
@Target(ElementType.PACKAGE)
@Retention(RetentionPolicy.RUNTIME)
public @interface TestAPackage {
 
}

/**
 * 简单的 Test-annotation
 */
public @interface TestA {
}

/**
 * 定义注解 Test 
 * 为方便测试：注解目标为类 方法，属性及构造方法 
 * 注解中含有三个元素 id ,name和 gid; 
 * id 元素 有默认值 0
 */ 
@Target({TYPE,METHOD,FIELD,CONSTRUCTOR})
@Retention(RetentionPolicy.RUNTIME)
public @interface TestAObject {
	String name();
	int id() default 0;
	Class<Long> gid();
}