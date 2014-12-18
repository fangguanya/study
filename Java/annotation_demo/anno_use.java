package com.fanggang.annotation;

import java.util.HashMap;
import java.util.Map;

// !< 测试之前定义的注解
@FAnnotaion
public class FUseAnnotation
{
	@FAnnotation
	private Integer age;

	@FAnnotation
	public FUseAnnotation()
	{
		@FAnnotation
		Map m = new HashMap(0);
	}

	public void b(@FAnnotation Integer a)
	{
	}
}

@FAnnotationTAll(name="type", gid=Long.class)
public class FUseAnnotationAll
{
	@FAnnotationTAll(name="param", id=1, gid=Long.class)
	private Integer age;

	@FAnnotationTAll(name="construct", id=2, gid=Long.class)
	public FUseAnnotationAll()
	{
	}

	@FAnnotationTAll(name="public method", id=3, gid=Long.class)
	public void a()
	{
		Map<String.String> m = new HashMap<String, String>(0);
	}

	@FAnnotationTAll(name="protected method", id=4, gid=Long.class)
	protected void b()
	{
		Map<String,String> m = new HashMap<String,String>(0);
	}

	@FAnnotationTAll(name="private method", id=5, gid=Long.class)
	private void c()
	{
		Map<String,String> m = new HashMap<String,String>(0);
	}

	public void b(Integer a)
	{
	}
}
