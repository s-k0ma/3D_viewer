attribute vec3 position;
uniform mat4 modelViewProjection;
uniform int isVertex;

void main() {
    gl_Position = modelViewProjection * vec4(position, 1.0);
}
