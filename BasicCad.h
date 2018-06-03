class BasicCad
{
	public:
		BasicCad(void);
		~BasicCad(void);
		static GLuint MakeShpere(const float& radius);
		static GLuint MakeCube(const float& size);
		static GLuint MakeBox(const float& length, const float& height, const float& width);
		static GLuint MakeCylinder(const float& radius, const float& length);
		static GLuint MakeOctagon(const float&  size, const float& thickness);
		static GLuint MakeFrustumShape(const float& bottom_size,const float& top_size,const float& height);
		static GLuint MakePyramid(const float& size, const float& height);
		static GLuint MakeCone(const float& base_rad,const float& length);
		static GLuint MakeTruncatedCone(const float& base_rad,const float& top_rad,const float& length);
};
