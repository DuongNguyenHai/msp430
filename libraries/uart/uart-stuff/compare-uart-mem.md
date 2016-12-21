			|			|			|			|			|
	uart v1		|	uart v2		| 	uart v3		|	energia		|	uart v4		|
			|			|			|			|			|

print : "hello" 
-------------------------------------------------------------------------------------------------------------------------

text  	566 		|	566		|	566		|	2482		|	562		|
data	0		|	0		|	0		|	2		|	0		|
bss	40		|	40		|	40		|	150		|	40		|
dec	606		|	606		|	606		|	2636		|	602		|
-------------------------------------------------------------------------------------------------------------------------

print : float number				|	
-------------------------------------------------------------------------------------------------------------------------

text  	4860 		|	4406		|	4792		|	6920		|	4788		|
data	0		|	0		|	0		|	2		|	0		|
bss	40		|	40		|	40		|	150		|	40		|
dec	4900		|	4446		|	4832		|	7072		|	4828		|
-------------------------------------------------------------------------------------------------------------------------

print : full of data 
-------------------------------------------------------------------------------------------------------------------------

text  	6046 		|	5818		|	5682		|	8448		|	5730		|
data	0		|	0		|	0		|	2		|	0		|
bss	40		|	40		|	40		|	158		|	40		|
dec	6086		|	5858		|	5722		|	8608		|	5770		|
-------------------------------------------------------------------------------------------------------------------------


-	uart v2 : Hàm print cho từng kiểu được viết rời với tên khác nhau (không overload function). Kết quả tiết kiệm 
	1kb so với bản uart v1. (hàm overload write() khiến bộ nhớ bị đây lên tận 1kb). In kiểu float tiết kiệm nhất. Khi
	print tất cả lại chiếm nhiều bộ nhớ nhất.

-	uart v3 : Không viết kiểu overload cho hàm print số. Sử dụng macro chuyển đổi kiểu cho số. Kết quả print kiểu 
	float tiết kiệm được một chút so với uart v1 nhưng khi gọi nhiều lần (đã test với 32 lần) thì sẽ tốn bộ nhớ hơn v1.

Kết luận :

1. Khi dùng ít hàm thì nên viết tách rời function (không overload) để tiết kiệm bộ nhớ. Điển hình là tiết kiệm ở version v2.
Nhưng khi sử dụng nhiều thì có thể viết kiểu overload funcion. Không nên viết kiểu template function, tuy nó tiết kiệm dòng 
code và quản lý hàm dẽ dàng hơn cho lập trình viên nhưng nó sẽ gây lãng phí bộ nhớ. Temaplate function khi được biên dịch nó
sẽ tự động tạo ra câc hàm có tham số với kiểu khác nhau -> gây lãng phí vì không dùng tất cả các kiểu, và nó còn gây khó kiểm
soát tham số.
