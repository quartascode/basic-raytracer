# Raytracer Básico

English: [README.md](README.md)

Raytracer simples feito a fim de estudos

## Recursos
- Superficies lambertiânas, materiais metálicos e dielétricos
- Intersecção de esferas
- Refração e reflexão total em dielétricos
- Movimentação da câmera e ponto o qual ela mira
- Fov vertical variável

## Exemplos
> **Obs.:** todos os exemplos são renderizados em 1080p com 1000 samples por pixel e um limite de 50 bounces

![Imagem #1](examples/image1.jpg)

![Imagem #2](examples/image3.jpg)

![Imagem #3](examples/image2.jpg)

## Como compilar
```sh
make raytracer && ./raytracer > image.ppm
```

## References
[Ray tracing in one weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html): um ótimo guia que apresente várias técnicas e teorias sobre raytracing
