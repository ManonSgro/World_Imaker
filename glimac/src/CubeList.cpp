/**
 * \file CubeList.cpp
 * \brief Gestion d'une liste de cube
 * \author MANSION Amélia & SGRO' Manon
 * \version 0.1
 * \date 20 décembre 2019
 *
 * Gestion d'une liste de cube dans la scène (addition/suppression/édition/affichage)
 *
 */

#include "glimac/CubeList.hpp"


namespace glimac {

    // Créer liste (vecteur), ajouter/supprimer cube, trier cubes selon texture ?
    CubeList::CubeList(){
        vboList.resize(1);
        vaoList.resize(1);
        iboList.resize(1);
    };
    CubeList::~CubeList(){};
    
    // Generate VBO
    void CubeList::generateVBO(){
        for(int i=0; i<m_cubeList.size(); i++){
            glGenBuffers(1, &vboList[i+1]);
            glBindBuffer(GL_ARRAY_BUFFER, vboList[i+1]);
            glBufferData(GL_ARRAY_BUFFER, this->getVertexCount(i)*sizeof(Vertex3DTexture), this->getDataPointer(i), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, vboList.back());
        }
    };

    // Generate VAO
    void CubeList::generateVAO(){
        for(int i=0; i<m_cubeList.size(); i++){
            glGenVertexArrays(1, &vaoList[i+1]);
            glBindVertexArray(vaoList[i+1]);
            glBindBuffer(GL_ARRAY_BUFFER, vboList[i+1]);
            glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
            glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, position));
            glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
            glVertexAttribPointer(VERTEX_ATTR_NORMAL,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, normal));
            glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
            glVertexAttribPointer(VERTEX_ATTR_TEXTURE,2,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, texture));

        }
    };
    
    // Generate IBO
    void CubeList::generateIBO(){
        for(int i=0; i<m_cubeList.size(); i++){
            glGenBuffers(1, &iboList[i+1]);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[i+1]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->getIBOCount(i)*sizeof(uint32_t), this->getIBOPointer(i), GL_STATIC_DRAW);
        }
    };

    // Set texture
    void CubeList::setTextureIndex(int index, GLuint textureIndex){
        m_cubeList[index].setTextureIndex(textureIndex);
    };

    // Set cube index
    void CubeList::setCubeIndex(int index, GLuint cubeIndex){
        m_cubeList[index].setCubeIndex(cubeIndex);
    }

    // Scale
    void CubeList::setScale(GLuint cubeIndex, GLfloat x, GLfloat y, GLfloat z){
        m_cubeList[cubeIndex].setScale(x, y, z);
    }
    // Rotate
    void CubeList::setRot(GLuint cubeIndex, GLfloat degrees, GLfloat x, GLfloat y, GLfloat z){
        m_cubeList[cubeIndex].setRot(degrees, x, y, z);
    }
    // Translate
    void CubeList::setTrans(GLuint cubeIndex, GLfloat x, GLfloat y, GLfloat z){
        m_cubeList[cubeIndex].setTrans(x, y, z);
    }

    // Push back a new cube at the end of the list
    void CubeList::addCube(Cube cube){
        m_cubeList.push_back(cube);
        m_cubeList[m_cubeList.size()-1].setCubeIndex(m_cubeList.size()-1);

        // VBO
        vboList.resize(vboList.size()+1);
        glGenBuffers(1, &vboList[vboList.size()-1]);
        glBindBuffer(GL_ARRAY_BUFFER, vboList[vboList.size()-1]);
        glBufferData(GL_ARRAY_BUFFER, this->getVertexCount(this->getSize()-1)*sizeof(Vertex3DTexture), this->getDataPointer(this->getSize()-1), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, vboList.back());

        //VAO
        vaoList.resize(vaoList.size()+1);
        glGenVertexArrays(1, &vaoList[vaoList.size()-1]);
        glBindVertexArray(vaoList[vaoList.size()-1]);
        glBindBuffer(GL_ARRAY_BUFFER, vboList[vaoList.size()-1]);
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glVertexAttribPointer(VERTEX_ATTR_POSITION,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, position));
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glVertexAttribPointer(VERTEX_ATTR_NORMAL,3,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, normal));
        glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
        glVertexAttribPointer(VERTEX_ATTR_TEXTURE,2,GL_FLOAT, GL_FALSE, sizeof(Vertex3DTexture), (const GLvoid*)offsetof(Vertex3DTexture, texture));

        //IBO
        iboList.resize(iboList.size()+1);
        glGenBuffers(1, &iboList[iboList.size()-1]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboList[iboList.size()-1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->getIBOCount(this->getSize()-1)*sizeof(uint32_t), this->getIBOPointer(this->getSize()-1), GL_STATIC_DRAW);
    }

    // Erase a cube at index "index" if exists
    void CubeList::deleteCube(int index){
        if(index<=m_cubeList.size()){
            m_cubeList.erase(m_cubeList.begin()+index);
            std::cout<< "Erase cube " << index <<std::endl;
        }
        for(int i=0;i<m_cubeList.size();i++){
            m_cubeList[i].setCubeIndex(i);
        }

        // Reset VBO/VAO/IBO
        if(index<=vboList.size()+1){
            glDeleteBuffers(1, &iboList[index+1]);
            iboList.erase(iboList.begin()+index+1);
            glDeleteVertexArrays(1, &vaoList[index+1]);
            vaoList.erase(vaoList.begin()+index+1);
            glDeleteBuffers(1, &vboList[index+1]);
            vboList.erase(vboList.begin()+index+1);
        }

        
    }

    // Sort cubes according to texture
    void CubeList::sortCubes(){
        std::sort(m_cubeList.begin(), m_cubeList.end(), std::greater<Cube>());
    }

    // Print cubes
    void CubeList::printCubes(){
        for(int i=0; i<m_cubeList.size(); i++){
            std::cout << "Index " << i << ": " << m_cubeList[i].getTextureIndex() << "-- cube index: " << m_cubeList[i].getCubeIndex() << std::endl;
        }
    }

    //Renvoit la matrice de poids
    Eigen::VectorXd CubeList::radialBasisFunction(Eigen::MatrixXd points, std::string rbf, float epsilon){
        // Solve distances*w = z
        int rows = points.rows();
        int cols = points.cols();
        Eigen::MatrixXd A(rows, rows);
        Eigen::VectorXd x(points.rows()), b(points.rows());
        //fill A
        for(int pointI=0; pointI<points.rows(); pointI++){
            for(int pointJ=0; pointJ<points.rows(); pointJ++){
                float distance = sqrt(pow(points(pointJ,0) - points(pointI, 0), 2) +  
                pow(points(pointJ,1) - points(pointI, 1), 2) +  
                pow(points(pointJ,2) - points(pointI, 2), 2));
                // RBF
                if(rbf == "default"){ //ok
                    A(pointI,pointJ) = distance;
                }else if(rbf == "multiquadric"){ //ok
                    A(pointI,pointJ) = sqrt(1+pow(distance,2));
                }else if(rbf == "inverse_quadratic"){ //ok
                    A(pointI,pointJ) = -1/(1+pow(epsilon*distance,2))-0.5;
                }else if(rbf == "inverse_multiquadric"){ //ok
                    A(pointI,pointJ) = -1/sqrt(1+pow(distance,2));
                }else if(rbf== "thin_plate_spline"){
                    A(pointI,pointJ) = pow(distance,2)*log10(distance);
                }else if(rbf== "gaussian"){ //ok
                    A(pointI,pointJ) = -exp(-pow(epsilon*distance,2))-0.5;
                }else if(rbf=="bump"){
                    if(distance<(1/epsilon)){
                        A(pointI,pointJ) = exp(-(1/(1-pow(distance,2))));
                    }else{
                        A(pointI,pointJ) = 0;
                    }
                }
            }
        }
        //fill b
        for(int i=0; i<points.rows(); i++){
            b(i) = points(i, 1);
        }
        x = A.colPivHouseholderQr().solve(b);
        return x;
    }

    //Entrée: x et y random dans l'enceinte de la grille -- Sortie : z calculé grâce aux poids trouvés au-dessus
    double CubeList::interpolatePoints(double x, double z, Eigen::MatrixXd points, std::string rbf, float epsilon){
        double y=0;
        Eigen::VectorXd w = this->radialBasisFunction(points, rbf, epsilon);
        for(int i=0; i<points.rows(); i++){
            double distance = sqrt(pow(points(i,0) - x, 2) +  
                pow(points(i,2) - z, 2) +  
                pow(points(i,1) - 0, 2) * 1.0);
            y += w(i)*distance;
        }
        return (int)y;
    }

    void CubeList::save(std::string filepath, int item_LightD, std::vector<int> positionLightD, int item_LightP, std::vector<int> positionLightP, std::vector<int> lightIntensity){
        std::ofstream file;
        file.open(filepath);
        if (!file) {
                std::cout << "Unable to open file";
                exit(1); // terminate with error
            }
        for(int i=0; i<m_cubeList.size(); i++){
            file << std::to_string(m_cubeList[i].getCubeIndex())+" "
            +std::to_string((int)m_cubeList[i].getTrans().x)+" "
            +std::to_string((int)m_cubeList[i].getTrans().y)+" "
            +std::to_string((int)m_cubeList[i].getTrans().z)+" "
            +std::to_string(m_cubeList[i].getTextureIndex())+" "+"\n";
        }
        // Write lights
        file << std::to_string(item_LightD)+" "
        +std::to_string(positionLightD[0])+" "
        +std::to_string(positionLightD[1])+" "
        +std::to_string(positionLightD[2])+" "
        +std::to_string(lightIntensity[0])+"\n";

        file << std::to_string(item_LightP)+" "
        +std::to_string(positionLightP[0])+" "
        +std::to_string(positionLightP[1])+" "
        +std::to_string(positionLightP[2])+" "
        +std::to_string(lightIntensity[1])+"\n";
        
        file.close();
    };

    void CubeList::read(std::string filePath, std::vector<int> &destination){
        int x;
        std::ifstream loadFile;
        loadFile.open(filePath);
        if (!loadFile) {
            std::cout << "Unable to open file";
            exit(1); // terminate with error
        }
        while (loadFile >> x) {
            destination.push_back(x);
        }
        loadFile.close();
    }

    void CubeList::load(std::vector<int> file, std::vector<int> &cursorPosition, int &currentActive, int &item_LightD, std::vector<int> &positionLightD, int &item_LightP, std::vector<int> &positionLightP, std::vector<int> &lightIntensity){
        std::cout << "Loading... " << (file.size()-2)/5 << "...cubes" << std::endl; 
        for(int i=0; i<file.size()-10; i+=5){
            this->addCube(Cube());
            this->setTrans(file[i], file[i+1],file[i+2],file[i+3]);
            this->setTextureIndex(file[i], file[i+4]);
            if(this->getTrans(i).x==cursorPosition[0] && this->getTrans(i).y==cursorPosition[1] && this->getTrans(i).z==cursorPosition[2]){
                currentActive = this->getSize()-1;
            }
        }
        item_LightD = file[file.size()-10];
        positionLightD = {file[file.size()-9], file[file.size()-8],file[file.size()-7]};
        lightIntensity[0] = file[file.size()-6];
        item_LightP = file[file.size()-5];
        positionLightP = {file[file.size()-4], file[file.size()-3],file[file.size()-2]};
        lightIntensity[1] = file[file.size()-1];
    }

}

