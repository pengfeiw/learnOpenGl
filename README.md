# Learn OpenGl

[learnOpengl-cn](https://learnopengl-cn.github.io/) 的练习。

## 渲染管线

OpenGL的大部分工作都是关于把3D坐标转变为适应你屏幕的2D像素。3D坐标转为2D坐标的处理过程是由OpenGL的图形渲染管线管理。

- 3D 坐标转换为 2D。
- 2D 坐标转换为实际有颜色的像素。

图形渲染管线可以被划分为几个阶段，每个阶段将会把前一个阶段的输出作为输入。

### 着色器

显卡都有成千上万的小处理核心，它们在GPU上为每一个（渲染管线）阶段运行各自的小程序，从而在图形渲染管线中快速处理你的数据。这些小程序叫做**着色器(Shader)**。

着色器编程：着色器可以由开发者配置，因为允许用自己写的着色器来代替默认的，所以能够更细致地控制图形渲染管线中的特定部分了。

OpenGL着色器是用OpenGL着色器语言(OpenGL Shading Language, **GLSL**)写成的。

> 顶点数据 -> 顶点着色器 -> 图元装配 -> 光栅化 -> 片段着色器 -> 测试与混合（Tests AND Blending）

- 顶点着色器(Vertex Shader)：把3D坐标转为另一种3D坐标。
- 几何着色器(Geometry Shader)：将一组顶点作为输入，这些顶点形成图元，并且能够通过发出新的顶点来形成新的(或其他)图元来生成其他形状。
- 图元装配(Primitive Assembly)：顶点着色器（或几何着色器）输出的所有顶点作为输入（如果是GL_POINTS，那么就是一个顶点），并将所有的点装配成指定图元的形状。
- 光栅化阶段(Rasterization Stage)：，这里它会把图元映射为最终屏幕上相应的像素，生成供片段着色器(Fragment Shader)使用的片段(Fragment)。在片段着色器运行之前会执行裁切(Clipping)。裁切会丢弃超出你的视图以外的所有像素，用来提升执行效率。
- 片段着色器：主要目的是计算一个像素的最终颜色，这也是所有OpenGL高级效果产生的地方。
- Alpha测试和混合(Blending)：检测片段的对应的深度和模板(Stencil)值,也会检查alpha值（alpha值定义了一个物体的透明度）并对物体进行混合(Blend)。

我们打算做渲染的话，现代OpenGL需要我们至少设置一个顶点和一个片段着色器。

### 标准化设备坐标(Normalized Device Coordinates, NDC)

一旦你的顶点坐标已经在顶点着色器中处理过，它们就应该是标准化设备坐标了，标准化设备坐标是一个**x、y和z值在-1.0到1.0**的一小段空间。任何落在范围外的坐标都会被丢弃/裁剪，不会显示在你的屏幕上。

OpenGL不是简单地把所有的3D坐标变换为屏幕上的2D像素；OpenGL仅当3D坐标在3个轴（x、y和z）上-1.0到1.0的范围内时才处理它。所有在这个范围内的坐标叫做标准化设备坐标(Normalized Device Coordinates，NDC)，此范围内的坐标最终显示在屏幕上（在这个范围以外的坐标则不会显示）。

### glViewport

glViewport 函数提供的数据，进行视口变换(Viewport Transform)，标准化设备坐标(Normalized Device Coordinates)会变换为屏幕空间坐标(Screen-space Coordinates)。所得的屏幕空间坐标又会被变换为片段输入到片段着色器中。 

### 顶点缓冲对象（VBO）

定义顶点数据以后，会把它作为输入发送给图形渲染管线的第一个处理阶段：顶点着色器。它会在GPU上创建 **内存**用于储存我们的顶点数据，还要配置OpenGL如何解释这些内存，并且指定其如何发送给显卡。通过**顶点缓冲对象(Vertex Buffer Objects, VBO)**管理这个内存，它会在GPU内存（通常被称为显存）中储存大量顶点。

使用glGenBuffers函数生成一个带有缓冲ID的VBO对象，顶点缓冲对象的缓冲类型是GL_ARRAY_BUFFER：
```
unsigned int VBO;
glGenBuffers(1, &VBO);
```

OpenGL允许我们同时绑定多个缓冲，只要它们是不同的缓冲类型。我们可以使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上：
```
glBindBuffer(GL_ARRAY_BUFFER, VBO);  
```

绑定缓冲后，我们使用的任何（在GL_ARRAY_BUFFER目标上的）缓冲调用都会用来配置当前绑定的缓冲(VBO)。然后我们可以调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中：
```
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
```

每个顶点属性从一个VBO管理的内存中获得它的数据，而具体是从哪个VBO（程序中可以有多个VBO）获取则是通过在调用glVertexAttribPointer时绑定到GL_ARRAY_BUFFER的VBO决定的。

### 顶点数组对象（VAO）

每个物体的绘制需要与绑定不同的顶点缓冲对象，所以 opengl 再绘制时，需要不断的切换 VBO，设置顶点属性指针，设置顶点数据，非常麻烦。

所以引入顶点数组对象，可以像顶点缓冲对象那样被绑定，任何随后的顶点属性调用都会储存在这个VAO中。这样的好处就是，当配置顶点属性指针时，你只需要将那些调用执行一次，之后再绘制物体的时候只需要绑定相应的VAO就行了。

要想使用VAO，要做的只是使用glBindVertexArray绑定VAO。从绑定之后起，我们应该绑定和配置对应的VBO和属性指针，之后解绑VAO供之后使用。当我们打算绘制一个物体的时候，我们只要在绘制物体前简单地把VAO绑定到希望使用的设定上就行了。这段代码应该看起来像这样：
```
// ..:: 初始化代码（只运行一次 (除非你的物体频繁改变)） :: ..
// 1. 绑定VAO
glBindVertexArray(VAO);
// 2. 把顶点数组复制到缓冲中供OpenGL使用
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 3. 设置顶点属性指针
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

[...]

// ..:: 绘制代码（渲染循环中） :: ..
// 4. 绘制物体
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
someOpenGLFunctionThatDrawsOurTriangle();
```

### 元素缓冲对象（索引缓冲对象）(EBO/IBO)

减少重复顶点的内存消耗。存储 OpenGL 用来决定要绘制哪些顶点的索引。这种所谓的索引绘制(Indexed Drawing)正是我们问题的解决方案。

```
// ..:: 初始化代码 :: ..
// 1. 绑定顶点数组对象
glBindVertexArray(VAO);
// 2. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
// 4. 设定顶点属性指针
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);

[...]

// ..:: 绘制代码（渲染循环中） :: ..
glUseProgram(shaderProgram);
glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
glBindVertexArray(0);
```