#include "sort.h"

void insertSort(int* a, int n) {
	if (a == NULL || n==0) {
		printf("传入的数据为空，无法排序！");
		return;
	}
	/*int front = a[0], latter = a[0], len = sizeof(a) / sizeof(a[0]) - 1;
	if (n > len) {
		n = len;
	}*/
	int front = a[0], latter = a[0];
	for (int i = 1; i < n; i++) {
		front = a[i - 1];
		latter = a[i];
		for (int j = i - 1; j >= 0; j--) {
			
			if (latter > front) {
				break;
			}
			//把较大的数据移到后边
			if (a[j] > latter ) {
				a[j + 1 ] = a[j];
				//如果比第一个元素小，则插在第一个位置
				if (j == 0)
					a[j] = latter;
				continue;
			}
			//找到比它小的数，插到它后面
			else if(a[j] <= latter)
			{
				a[j + 1] = latter;
				break;
			}
		}
	}
}

void Merge(int* a, int begin, int mid, int end, int* temp) {
 	int i = begin, j = mid + 1, k = 0;
	while (i <= mid && j <= end) {
		//给子数组排序
		if (a[i] <= a[j]) {
			temp[k] = a[i];
			i++;
		}
		else {
			temp[k] = a[j];
			j++;
		}
		k++;
	}
	while (i <= mid)
	{
		temp[k] = a[i];
		i++;
		k++;
	}
	while (j <= end) {
		temp[k] = a[j];
		j++;
		k++;
	}
	//将排序好的元素
	for (int i = 0; i < k; i++) {
		a[begin + i] = temp[i];
	}

}

void MergeArray(int* a, int begin, int mid, int end, int* temp) {
	//用递归的思想把数组不断划分直至子数组只剩一个元素
	if (begin < end ) {
		MergeArray(a, begin, (begin + mid) / 2, mid, temp);
		MergeArray(a, mid + 1, (mid + 1 + end) / 2, end, temp);
		Merge(a, begin, mid, end, temp);
	}
}

void MergeSort(int* a, int begin, int end, int* temp) {
	if (begin >= end)
		return;
	//用递归先把数组划分
	int mid = (begin + end) / 2;
	MergeSort(a, begin, mid, temp);
	MergeSort(a, mid + 1, end, temp);
	int i = begin, j = mid + 1, k = 0;
	while (i <= mid && j <= end) {
		if (a[i] <= a[j]) {
			temp[k++] = a[i++];
		}
		else
		{
			temp[k++] = a[j++];
		}
	}
	while (i <= mid)
		temp[k++] = a[i++];
	while (j <= end)
		temp[k++] = a[j++];
	for (i = 0; i < k; i++)
		a[begin + i] = temp[i];
}

void QuickSort_Recursion(int* a, int begin, int end) {
	if (a == NULL) {
		printf("传入的数据为空，无法排序！");
		return;
	}
	if (begin > end)
		return;
	/*int len = (sizeof(a) / sizeof(a[0])) - 1;
	if (end > len) {
		end = len;
	}*/
	int key = a[begin], b = begin, e = end, change ;
	while (b != e) {
		//从数组右边开始找出比key小的数
		while (a[e] >= key && e > b) {
			e--;
		}
		//从数组左边开始找出比key大的数
		while (a[b] <= key && e > b)
		{
			b++;
		}
		//交换那两个数
		if (e > b) {
			change = a[e];
			a[e] = a[b];
			a[b] = change;
		}
	}
	//如果没有交换的那个元素比key大，那就拿那个元素前一元素与key交换
	if (a[b] > key)
	{
		//a[b-1]必定比key小
		change = a[b - 1];
		a[b - 1] = a[begin];
		a[begin] = change;
	}
	else
	{
		//如果最后没有交换的那个元素比key小，两者就交换；
		change = a[b];
		a[b] = a[begin];
		a[begin] = change;
	}
	//用递归不断对两边快排
	QuickSort_Recursion(a, begin, b - 1);
	QuickSort_Recursion(a, b + 1, end);
}

void QuickSort(int* a, int size) {
	//
	int* stack = (int*)malloc(size * sizeof(int));
	int top = -1, begin = 0, end = 0;
	//首尾位置先后入栈
	if (top < size - 1) {
		stack[++top] = 0;
		stack[++top] = size - 1;
	}
	//栈顶不为-1，则不是空栈
	while (top >= 0)
	{
		//首尾位置先后出栈
		end = stack[top--];
		begin = stack[top--];
		//以中间数为枢轴
		int pivot = a[(begin + end) / 2];
		int i = begin, j = end, change = 0;
		while (i < j) {
			//从左边找出比枢轴大的元素
			while (a[i] < pivot)
				i++;
			//从右边找出比枢轴大的元素
			while (a[j] > pivot)
			{
				j--;
			}
			//在两者没有交叉访问的时候互换
			if (i <= j) {
				change = a[i];
				a[i] = a[j];
				a[j] = change;
				i++;
				j--;
			}
		}
		//当j没有走到数组首位置,i没有走到数组尾位置
		if (begin < j) {
			stack[++top] = begin;
			stack[++top] = j;
		}
		if (i < end) {
			stack[++top] = i;
			stack[++top] = end;
		}

	}
}

int Partition(int* a, int begin, int end) {
	if (begin >= end)
		return 0;
	//找第一个元素当枢轴
	int pivot = a[begin], i = begin, j = end;
	while (i < j) {
		//从右边找比枢轴小的元素
		while (a[j] >= pivot && i < j)
			j--;
		
		a[i] = a[j];
		//从左边找比枢轴大的元素
		while (a[i] <= pivot && i < j)
		{
			i++;
		}
		a[j] = a[i];
	}
	//上诉循环把枢轴记下的那个元素覆盖掉了，现在赋值回去
	a[j] = pivot;
	//用递归对左右两边快排
	Partition(a, begin, i - 1);
	Partition(a, i + 1, end);
	//return 1;
}

void QuickSort_Random(int* a, int begin, int end) {
	if (begin > end)
		return;
	//获得随机一个元素当枢轴
	int random = ((rand() % (end - begin + 1)) + begin);
	int b = begin, e = end, pivot = a[begin], change;
	a[begin] = a[random];
	a[random] = pivot;
	//将随机元素换到首位置
	pivot = a[begin];
	while (b != e) {
		while (a[e] >= pivot && e > b) {
			e--;
		}
		while (a[b] <= pivot && e > b)
		{
			b++;
		}
		if (e > b) {
			change = a[e];
			a[e] = a[b];
			a[b] = change;
		}
	}
	//快排好后，将枢轴与一个比枢轴小的数互换
	if (a[b] > pivot)
	{
		change = a[b - 1];
		a[b - 1] = a[begin];
		a[begin] = change;
	}
	else
	{
		change = a[b];
		a[b] = a[begin];
		a[begin] = change;
	}
	QuickSort_Random(a, begin, b - 1);
	QuickSort_Random(a, b + 1, end);

} 

void QuickSort_Three(int* a, int begin, int end, int mid) {
	if (a == NULL) {
		printf("传入的数据为空，无法排序！");
		return;
	}
	//取中间的元素为枢轴
	int pivot = a[begin], x1 = a[begin], x2 = a[mid], x3 = a[end];
	if (x1 <= x2 && x2 <= x3) {
		a[begin] = x2;
		a[mid] = pivot;
	}
	else if(x2 <= x3 && x3 <= x1)
	{
		a[begin] = x3;
		a[end] = pivot;
	}
	//并将枢轴移到首位置
	pivot = a[begin];
	if (begin > end)
		return;
	int b = begin, e = end, change;
	while (b != e) {
		while (a[e] >= pivot && e > b) {
			e--;
		}
		while (a[b] <= pivot && e > b)
		{
			b++;
		}
		if (e > b) {
			change = a[e];
			a[e] = a[b];
			a[b] = change;
		}
	}
	if (a[b] > pivot)
	{
		change = a[b - 1];
		a[b - 1] = a[begin];
		a[begin] = change;
	}
	else
	{
		change = a[b];
		a[b] = a[begin];
		a[begin] = change;
	}
	int mid1 = (begin + b - 1) / 2, mid2 = (b + 1 + end) / 2;
	a[b] = pivot;
	QuickSort_Three(a, begin, b - 1, mid1);
	QuickSort_Three(a, b + 1, end, mid2);
}

void CountSort(int* a, int size, int max) {
	/*int len = sizeof(a) / sizeof(a[0]), max1 = max + 1;
	if (size > len) {
		size = len;
	}*/
	if (size <= 0 || max <= 0) {
		return;
	}
	//给计数数组开辟一个大一点的内存空间
	int max1 = max + 1;
	int* p = (int*)malloc(max1 * sizeof(int)), * p2 = (int*)malloc(size * sizeof(int));
	int num;
	//将计数数组初始化为0，否则影响结果
	for (int i = 0; i <= max; i++) {
		p[i] = 0;
	}
	for (int i = 0; i < size; i++) {
		p2[i] = a[i];
	}
	//计数
	for (int i = 0; i < size; i++) {
		num = a[i];
		p[num] += 1;
	}
	//逐个累加，其对应元素的值就是其位置
	for (int i = 1; i <= max; i++) {
		p[i] += p[i - 1];
	}
	//根据计数数组的下标与其对应的值赋值给a数组
	for (int i = size - 1 ; i >= 0; i--) {
		num = p2[i];
		a[p[num] - 1] = p2[i];
		p[num] -= 1;
	}
	free(p);
	free(p2);
}

void RadixCountSort(int* a, int size) {
	if (size <= 0) {
		return;
	}
	int max = a[0];
	//找出最大值
	for (int i = 0; i < size; i++) {
		if (a[i] > max)
			max = a[i];
	}
	int max1 = max + 1, radix = 1;
	int* p = (int*)malloc(size * sizeof(int)), * count = (int*)malloc(sizeof(int) * max1);
	while (max / radix > 0) {
		for (int i = 0; i <= max; i++)
			count[i] = 0;
		for (int i = 0; i < size; i++)
			count[a[i] / radix % 10] += 1;
		for (int i = 1; i <= max; i++)
			count[i] += count[i - 1];
		for (int i = size - 1; i >= 0; i--)
			p[--count[a[i] / radix % 10]] = a[i];
		for (int i = 0; i < size; i++)
			a[i] = p[i];
		//
		radix *= 10;
	}

	free(count);
	free(p);
}

void ColorSort(int* a, int size) {
	if (a == NULL) {
		printf("传入的数据为空，无法排序！");
		return;
	}
	/*int m, len = sizeof(a) / sizeof(a[0]);
	if (size > len) {
		size = len;
	}*/
	int m;
	int* p1 = a, * p2 = a + size - 1, * p = a;
	for (int i = 0; i < size; i++) {
		//使p指向不为0的元素
		for (; *p == 0;) {
			p++;
		}
		//如果p1指向0，就和不指向0的p交换
		if (p1[i] == 0 && (&p1[i]) > p) {
			m = p1[i];
			p1[i] = *p;
			*p = m;
			p++;
		}
		else if(p1[i] == 2)
		{
			//如果p1指向2，就和不指向2的p2交换
			m = p1[i];
			p1[i] = *p2;
			*p2 = m;
			p2--;
		}
		//使p2指向不为2的元素
		for (; *p2 == 2;) {
			p2--;
		}
		//如果p1[i]的地址，与p2指向的地址一样，就退出循环
		if(&p1[i] == p2)
		{
			break;
		}
	}
}

