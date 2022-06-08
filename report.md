
# Student Information

student name: 김소정

student id: 20205031


# Intro

Ray tracing은 화면에 이미지를 구성할 때, 관찰자의 위치에서부터 화면의 각 픽셀에 ray를 쏘아 표현하고자 하는 공간에서 어떻게 빛이 서로 반사되는지를 확인하여 픽셀 값을 계산하는 방법이다. ray가 object와 만나는지를 확인한 후 object와 제일 먼저 만나는 점을 찾는다. 만약 만나지 않는다면 background color를, object와 만난다면 값을 계산하여 픽셀에 넣는다. 

object의 재질 특성마다 빛을 계산하는 방법이 서로 다르기 때문에 각각 어떻게 계산할지를 정해 주어야 한다. 해당 과제에서는 고르게 반사하는 diffuse, 거울과 비슷하지만 더 뿌옇게 반사하는 metal, 빛이 굴절되는 투명한 dielectric 세 개의 material을 구현한다.

기본적으로는 픽셀의 가운데 점에서 ray를 만들지만, 한 개의 픽셀마다 한 개의 ray만 사용하면, 선명하게 이미지가 만들어지지 않고 aliasing이 발생한다. 이를 해결하기 위해서는(antialiasing) 한 픽셀마다 여러 개의 ray를 쏘아 평균치를 내는 방법을 사용할 수 있다.

빨간색 종이를 얼굴에 대면 붉은 끼가 반사되는 것처럼, light가 object를 만나 반사되면서 bounce하면 다른 object에도 영향을 미친다. 이를 indirect lighting이라고 한다.

direct light는 light가 한 번 반사되어 눈에 도달하는 것으로, light source가 area light일 경우 이를 sampling하여 light point들을 만든다. 이후 camera에서 만든 ray가 light에 도달하지 못하면 물체에 가려진 것으로 판단하여 ray가 만난 지점에 shadow 처리를 한다.

# Task report


## Task: Antialiasing

* Default

![default1](https://user-images.githubusercontent.com/78066907/172670650-53d1d2cb-7693-4a9a-996f-a2bc61568536.png)

	아무것도 적용하지 않았을 때의 기본 이미지이다. 4개의 object가 있다. 

* Before antialiasing

![diffuse](https://user-images.githubusercontent.com/78066907/172670782-c2fc78ba-17c7-4c94-9fae-063a0ff10191.png)

	한 픽셀당 한 개의 ray만 사용하였을 때의 사진이다. 보다시피 화질이 낮고 노이즈가 많아 보인다.

* Applied antialiasing

![antialiasing](https://user-images.githubusercontent.com/78066907/172671000-68ca4dcb-2710-4a42-9080-bb2ea25e0555.png)

	한 픽셀당 64개의 sample ray를 사용했을 때이다. 
	main()함수에서, camera에서 나온 ray를 바로 사용하지 않고 for문을 사용하여 한 픽셀 안에서 여러 개의 sample ray를 만들었다.
	random float를 만들어서 해당 픽셀의 x,y좌표에 더하는 방식인 random sampling을 적용했다. 
	이렇게 만들어진 sample ray들로 계산한 평균값을 해당 픽셀의 rgb값으로 사용했다.
	
![final](https://user-images.githubusercontent.com/78066907/172687428-5963825d-2c68-4165-bf07-82153947b11e.png)

	위 사진은 최종 결과이며, 1024spp일 때이다.  

## Task: Indirect lighting

* Indirect lighting

![indirect lighting](https://user-images.githubusercontent.com/78066907/172676713-1c508215-2e5d-4794-81b7-30cdfd256b9c.png)

	가운데 물체를 확인하면 밑에 분홍색 그림자가, 양 옆의 물체에 분홍색 반사광이 약간 생긴 것을 볼 수 있다. 
	indirect lighting을 구현하기 위해서 integrator의 integrate() 함수를 recursive하게 구성하였다. 
	가장 먼저 primary ray를 scene에 쏘아 object와 만나는지를 확인한다. 
	만난다면, 표면에서 scatter되는지를 확인하고, scatter한다면 secondary ray를 계산한다. 
	위 사진은 세 물체 다 diffuse라고 가정하여서 ray가 물체와 만나면 항상 scatter한다고 설정하였다. 
	그렇게 만들어진 secondary ray를 다시 scene에 primary ray처럼 보내서 다른 물체와 만나는지를 확인하였다. 
	끝없이 반복되면 안되기 때문에 depth(=50)를 설정하였다. 
	이렇게 반복하며 나온 값에 albedo를 곱하여 최종 결과값을 만들어 pixel에 넣어 주었다. 

* Dark Background light

![dark light](https://user-images.githubusercontent.com/78066907/172677326-046f8586-3f38-4320-be66-9520e0158227.png)

	최종 결과에서 background light를 어둡게 설정하였을 때이다. Indirect lighting에서 각 물체의 특성이 잘 보이기에 첨부하였다. 


## Task: Material

1. Diffuse

![antialiasing](https://user-images.githubusercontent.com/78066907/172671000-68ca4dcb-2710-4a42-9080-bb2ea25e0555.png)

	앞서 보았던 사진이지만 처음에 Diffuse material부터 구현하였기 때문에 다시 이 사진을 사용했다. 
	처음에는 integrator의 integrate 함수를 수정해서 만들었기 때문에, indirect lighting까지 구현되었다. 
	이 때의 diffuse에서는 albedo로 그냥 0.5를 사용하여 색이 적용되지 않았다. 
	primary ray가 object를 hit하면 hit한 물체의 표면에서 생성되는 secondary ray의 방향을 random하게 만들어서 diffuse 성질을 표현했다. 
	이후 scatter() 함수를 수정해서 항상 true를 return하게 해서, integrate()에서 재귀적으로 diffuse material의 표면 색을 계산해 주었다. 
	attenuation()은 간단하게 return color_로 구성하여 integrate()에서 albedo로 사용하였다. 

2. metal

![glossy](https://user-images.githubusercontent.com/78066907/172677231-4ad664ee-a677-4831-a774-2884c141fbd6.png)

	처음에는 perfect mirror처럼 구성했다. 
	이 때부터 materal.cpp의 각 함수를 사용하기 시작하여, scatter()를 수정하였다. 
	diffuse와 마찬가지로 albedo=attenation()으로 clolor_값을 사용하였다. 
	scatter()에서는 input ray와 표면 normal로 reflection 방향을 계산하여 secondary ray를 만든다.
	이 ray가 유효한지 확인한 후 true를 return하여 integrate()에서 사용하였다. 

![metal diffuse](https://user-images.githubusercontent.com/78066907/172676736-1808733e-2d02-4a42-8665-249d01ae73c1.png)

	mirror의 perfect reflection에 randomness를 추가하여 metal처럼 보이게 만들었다. 
	reflection의 방향벡터에 random한 숫자를 더해 주어 구현했다. diffuse도 수정하여 완전히 구현했다.

3. dielectric

![dilectric](https://user-images.githubusercontent.com/78066907/172676832-5564ba77-77d4-4589-9d61-ce38d663404f.png)

	dielectric에서는 refraction rate도 input으로 받아서 IOR_로 저장한다. 
	scatter()에서는 input ray와 normal을 이용하여 Snell's law에 따라 refract하는 정도를 계산하여 output ray로 바꿔준다. 
	glass는 빛을 흡수하지 않으므로 attenuation()=(1,1,1)로 두어 albedo로 사용했다. 
	front_face인지에 따라 IOR_, 1/IOR_를 refraction ratio로 사용했다. 

