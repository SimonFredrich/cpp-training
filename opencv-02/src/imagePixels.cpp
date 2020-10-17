#include "imagePixels.h"
#include <iostream>

vector<Vec3b> getPixelValues(const Mat &img)
{
	vector<Vec3b> temp;
	for (size_t col = 0; col < img.cols; col++)
	{
		for (size_t row = 0; row < img.rows; row++)
		{
			temp.push_back(img.at<Vec3b>(row, col));
		}
	}
	return temp;
}

void swapping(Vec3b &a, Vec3b &b)
{
	Vec3b temp;
	temp = a;
	a = b;
	b = temp;
}

void sortPixelValues(vector<Vec3b> &vals)
{
	/* a[0] to a[aLength-1] is the array to sort */
	size_t i, j;
	size_t aLength = vals.size(); // initialise to a's length

	/* advance the position through the entire array */
	/*   (could do i < aLength-1 because single element is also min element) */
	for (i = 0; i < aLength - 1; i++)
	{
		/* find the min element in the unsorted a[i .. aLength-1] */

		/* assume the min is the first element */

		int jMin = i;

		/* test against elements after i to find the smallest */
		for (j = i + 1; j < aLength; j++)
		{
			/* if this element is less, then it is the new minimum */
			if ((int)vals[j][0] < (int)vals[jMin][0])

			{

				/* found new minimum; remember its index */
				jMin = j;
			}
		}

		if (jMin != i)
		{
			swap(vals[i], vals[jMin]);
		}
	}
}

void test()
{
	vector<Vec3b> testVec = {
		Vec3b(33, 0, 8),
		Vec3b(66, 88, 0),
		Vec3b(33, 0, 8),
		Vec3b(93, 88, 0),
		Vec3b(0, 0, 8),
		Vec3b(39, 88, 0),
		Vec3b(28, 0, 8),
		Vec3b(49, 88, 0),
		Vec3b(39, 0, 8),
		Vec3b(20, 88, 0),
		Vec3b(39, 0, 8),
		Vec3b(27, 88, 0),
		Vec3b(220, 0, 8),
		Vec3b(92, 88, 0),
		Vec3b(93, 0, 8),
		Vec3b(93, 88, 0),
		Vec3b(28, 0, 8),
		Vec3b(209, 88, 0),
		Vec3b(34, 0, 8),
		Vec3b(67, 88, 0)};

	/* a[0] to a[aLength-1] is the array to sort */

	int i, j;

	int aLength = testVec.size(); // initialise to a's length

	/* advance the position through the entire array */

	/*   (could do i < aLength-1 because single element is also min element) */

	for (i = 0; i < aLength - 1; i++)

	{

		/* find the min element in the unsorted a[i .. aLength-1] */

		/* assume the min is the first element */

		int jMin = i;

		/* test against elements after i to find the smallest */

		for (j = i + 1; j < aLength; j++)

		{

			/* if this element is less, then it is the new minimum */
			//std::cout << (int)testVec[j][0] << std::endl;
			if ((int)testVec[j][0] < (int)testVec[jMin][0])

			{

				/* found new minimum; remember its index */

				jMin = j;
				//std::cout << "found new minimum" << std::endl;
			}
		}

		if (jMin != i)

		{

			swap(testVec[i], testVec[jMin]);
		}
	}
	for (size_t i = 0; i < testVec.size(); i++)
	{
		std::cout << (int)testVec[i][0] << std::endl;
	}
}