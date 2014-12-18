package com.fanggang.annotation;

import java.lang.annotation.Annotation;
import java.lang.reflect.Constructor;
import java.lang.reflect.Method;

public class FAnnotationLoader
{
	public static void parseTypeAnnotation() throws ClassNotFoundException
	{
		Class clazz = Class.forName("com.fanggang.annotation.FUseAnnotationAll");
		Annotation[] annotations = clazz.getAnnotations();
		for (Annotation annotation : annotations)
		{
			FAnnotationTAll tmp = (FAnnotationTAll)annotation;
			System.out.println("id = \"" + tmp.id() + "\"; name = \"" + tmp.name() + "\"; gid = " + tmp.gid());
		}
	}

	public static void parseMethodAnnotation()
	{
		Method[] methods = FUseAnnotationAll.class.getDeclaredmethods();
		for (Method method : methods)
		{
			boolean hasAnnotation = method.isAnnotationPresent(FAnnotationTAll.class);
			if (hasAnnotation)
			{
				FAnnotationTAll annotation = method.getAnnotation(FAnnotationTAll.class);
				System.out.println("method = " + method.getName() + " ; id = " + annotation.id() + " ; description = " + annotation.name() + " ; gid = " + annotation.gid());
			}
		}
	}

	public static void parseConstructAnnotation()
	{
		Constructor[] constructors = FUseAnnotationAll.class.getConstructors();
		for (Constructor constructor : constructors)
		{
			boolean hasAnnotation = constructor.isAnnotationPresent(FAnnotationTAll.class);
			if (hasAnnotation)
			{
				FAnnotationTAll annotation = (FAnnotationTAll)constructor.getAnnotation(FAnnotationTAll.class);
				System.out.println("constructor = " + constructor.getName() + " ; id = " + annotation.id() + " ; description = " + annotation.name() + " ; gid = " + annotation.gid());
			}
		}
	}

	public static void main(String[] args) throws ClassNotFoundException
	{
		parseTypeAnnotation();
		parseMethodAnnotation();
		parseConstructAnnotation();
	}
}
