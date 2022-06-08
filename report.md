# Student Information

student name: 김소정

student id: 20205031



# Task: Antialiasing

default
![default1](https://user-images.githubusercontent.com/78066907/172670650-53d1d2cb-7693-4a9a-996f-a2bc61568536.png)

아무것도 적용하지 않았을 때의 기본 이미지이다. 5개의 object가 있다. 


before antialiasing
![diffuse](https://user-images.githubusercontent.com/78066907/172670782-c2fc78ba-17c7-4c94-9fae-063a0ff10191.png)

한 픽셀당 한 개의 ray만 사용하였을 때의 사진이다. 보다시피 화질이 낮고 노이즈가 많아 보인다.


applied antialiasing
![antialiasing](https://user-images.githubusercontent.com/78066907/172671000-68ca4dcb-2710-4a42-9080-bb2ea25e0555.png)

한 픽셀당 64개의 sample ray를 사용했을 때이다. for문을 사용하여 한 픽셀 안에서 random float를 골라 x,y좌표에 더하는 방식으로 random sampling을 적용했다. 



# Task: Material



# Task: Indirect lighting




