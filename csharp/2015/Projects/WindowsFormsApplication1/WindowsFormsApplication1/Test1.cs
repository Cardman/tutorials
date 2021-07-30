using System;

using NUnit.Framework;

public class Class1
{
	public Class1()
	{

	}

    [TestCase(2, 2, 4)]
    public void Test1Sum(int _a, int _b, int _sum)
    {
        Assert.That(_a + _b, Is.EqualTo(_sum));
    }
}
