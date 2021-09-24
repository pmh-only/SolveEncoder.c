# SolveEncoder.c

[솔브언어 변환기](https://gist.github.com/thoratica/77d7ddfa039297d0aefeb8599aac409f)인데... C언어로 짬.

ㅓ... 나도 솔직히 어케 만든건지 모르겠음 대충 짜니까 잘 작동하더라

참고로 띠까님이 만든거랑 100% 호환됨

아마도 이 변환기가 가장 빠르겠지

## 빌드(컴파일)
걍 리눅 터미널에 `make` 치삼

## 인코딩
```./SolveEncoder encode 솔바브보```

출력:
```
바보바보바보솔브바보바보솔브솔브바보솔브솔브솔브솔브바보바보솔브바보솔브솔브바보솔브바보솔브솔브바보바보바보솔브바보솔브바보바보바보솔브바보바보솔브솔브솔브솔브바보솔브솔브바보솔브바보솔브솔브바보바보바보솔브바보솔브바보바보바보솔브바보바보바보솔브솔브솔브바보솔브솔브솔브바보바보솔브솔브바보바보바보솔브바보솔브바보바보바보솔브바보바보솔브솔브바보바보바보솔브바보바보솔브바보솔브솔브
```

![](https://cdn.discordapp.com/attachments/530043751901429762/890991182182776832/unknown.png)


## 디코딩
```./SolveEncoder decode 바보바보바보솔브바보바보솔브솔브바보솔브솔브솔브솔브바보바보솔브바보솔브솔브바보솔브바보솔브솔브바보바보바보솔브바보솔브바보바보바보솔브바보바보솔브솔브솔브솔브바보솔브솔브바보솔브바보솔브솔브바보바보바보솔브바보솔브바보바보바보솔브바보바보바보솔브솔브솔브바보솔브솔브솔브바보바보솔브솔브바보바보바보솔브바보솔브바보바보바보솔브바보바보솔브솔브바보바보바보솔브바보바보솔브바보솔브솔브 ```

출력:
```
솔바브보
```

![](https://cdn.discordapp.com/attachments/530043751901429762/890991666490658906/unknown.png)

## 윈도지원은?
아마 윈도에서도 잘 돌아갈꺼임 근데 내가 wchar.h 최신버전에 C11버전 컴파일러가 없어서 (깔기 귀찮) 컴파일을 못함
