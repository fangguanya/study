package com.fanggang.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Target;

public @interface FAnnotation
{
}

@Target(ElementType.PACKAGE)
@Retention(RetentionPolicy.RUNTIME)
public @interface FAnnotationTPackage
{
}

@Target({ElementType.TYPE,ElementType.METHOD,ElementType.FIELD,ElementType.CONSTRUCTOR})
@Retention(RetentionPolicy.RUNTIME)
public @interface FAnnotationTAll
{
	String name();
	int id() default 0;
	Class<Long> gid();
}
