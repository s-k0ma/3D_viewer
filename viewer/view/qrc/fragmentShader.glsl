uniform vec4 vertexColor;
uniform vec4 edgeColor;
uniform int isVertex;
uniform int drawMode;
uniform int vertexShape;

void main(){
    if(isVertex == 1){
        if(vertexShape != 2) gl_FragColor = vertexColor;
        else discard;
    }else{
        if(drawMode == 0){
            gl_FragColor = edgeColor;
        }
        if(drawMode == 1){
             float dotSpacing = 15.0; // Define your desired fixed space between dots
             ivec2 gridPosition = ivec2(gl_FragCoord.xy / dotSpacing); // Using fixed spacing
             if (mod(float(gridPosition.x + gridPosition.y), 2.0) > 0.5) {
                 discard; // Discard instead of setting alpha to 0
             } else gl_FragColor = edgeColor;
         }
    }
}