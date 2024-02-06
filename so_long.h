#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdio.h>

typedef struct	s_data {
	void	*img;
	/*
	Purpose: This pointer holds the reference to an image created by MiniLibX. When you call mlx_new_image,
	it returns a pointer to the newly created image, which is then stored in this variable.
	It's used in subsequent operations related to this specific image,
	such as getting its address in memory or displaying it in a window.
	*/
	char	*addr;
	/*
	Purpose: This character pointer stores the address of the memory location where the image's pixel data begins.
	After creating an image with mlx_new_image, you use mlx_get_data_addr to obtain this starting address.
	It's crucial for pixel manipulation,
	allowing direct access to modify the image's pixels.
	*/
	int		bits_per_pixel;
	/*
	Purpose: This integer value represents the number of bits used for each pixel in the image.
	It's often abbreviated as "bpp" and is essential for understanding how pixel colors are stored.
	For instance, a bpp of 32 means that each pixel uses 32 bits (or 4 bytes), typically allowing for millions of color combinations with an additional alpha channel for transparency.
	This value is set by mlx_get_data_addr and is used to calculate the correct position of each pixel within the image data.
	*/
	int		line_length;
	/*
	Purpose: This integer specifies the number of bytes used to store one line of the image in memory.
	It's important to note that this may not simply be the number of pixels in the width of the image multiplied by the bytes per pixel,
	due to potential padding at the end of each line for alignment purposes.
	This value is crucial for calculating the memory offset when writing pixels to specific locations in the image.
	*/
	int		endian;
	/*
	Purpose: This integer indicates the endianness of the pixel color data.
	Endianness refers to the order of the bytes comprising a word of digital data in computer memory.
	In the context of images, it affects how the color channels (such as Red, Green, Blue, and Alpha) are ordered in memory.
	A value of 0 typically indicates little-endian order (least significant byte stored first), while 1 indicates big-endian order (most significant byte stored first).
	This is important for correctly interpreting the color values of pixels.
	*/
}				t_data;

#endif