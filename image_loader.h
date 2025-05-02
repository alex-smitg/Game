



int load_image(std::string path, GLuint* texture_id) {
	int width, height, nrChannels;


	unsigned char* img = stbi_load(path.c_str(), &width, &height, &nrChannels, 4); //diff


	GLuint white = 0xFFFFFFFF;
	GLuint black = 0xFF000000;
	GLfloat pixels[12] = { 1.0f, 1.0f, 1.0f, 0.0f,  0.0f,  0.0f, 0.0f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, };

	if (!img) {
		std::cout
			<< "ERROR: can't load image at path: " << path << " "
			<< stbi_failure_reason()
			<< "\n";

		stbi_image_free(img);

		return 0;
	}

	GLenum format = GL_RGB;
	//if (nrChannels == 1)
		//format = GL_RED;
	if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;



	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	if (img) {
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	if (img) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	stbi_image_free(img);

	*texture_id = texture;

	return 1;
}




Texture* create_texture(std::string path) {
	Texture* texture = new Texture();
	GLuint texture_id;

	if (load_image(path, &texture_id)) {
		texture->id = texture_id;
		texture->path = path;
	}
	else {
		std::cout << "ERROR: Texture was not loaded";
	}

	return texture;

}