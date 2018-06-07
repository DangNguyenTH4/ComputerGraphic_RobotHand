class BasicCad
{
	public:
		BasicCad(void);
		~BasicCad(void);
		static GLuint MakeShpere(const float& radius);
		static GLuint MakeCube(const float& size);
		static GLuint MakeBox(const float& length, const float& height, const float& width);
		static GLuint MakeFrustumShape(const float& bottom_size,const float& top_size,const float& height);
		
};
