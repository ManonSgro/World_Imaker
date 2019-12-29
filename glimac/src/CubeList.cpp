#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include "glimac/common.hpp"
#include "glimac/CubeList.hpp"
#include<Eigen/SparseLU> 

namespace glimac {

    // Créer liste (vecteur), ajouter/supprimer cube, trier cubes selon texture ?
    CubeList::CubeList(){};
    CubeList::~CubeList(){};
    
    // Generate VBO
    void CubeList::generateVBO(std::vector<GLuint> &vboList){
        for(int i=0; i<m_cubeList.size(); i++){
            glGenBuffers(1, &vboList[i+1]);
            glBindBuffer(GL_ARRAY_BUFFER, vboList[i+1]);
            glBufferData(GL_ARRAY_BUFFER, this->getVertexCount(i)*sizeof(Vertex3DTexture), this->getDataPointer(i), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, vboList.back());
        }
    };

    // Generate VAO
    void CubeList::generateVAO(std::vector<GLuint> &vaoList, std::vector<GLuint> &vboList, GLuint VERTEX_ATTR_POSITION, GLuint VERTEX_ATTR_NORMAL, GLuint VERTEX_ATTR_TEXTURE){
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
    void CubeList::generateIBO(std::vector<GLuint> &iboList){
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

    // Push back origin in the list (prefer call it before pushing other cubes)
    void CubeList::addOrigin(){
        m_cubeList.push_back(Cube());
        m_cubeList[m_cubeList.size()-1].setScaleFloat(0.1,0.1,0.1);
        m_cubeList[m_cubeList.size()-1].setCubeIndex(m_cubeList.size()-1);
    }

    // Push back a new cube at the end of the list
    void CubeList::addCube(Cube cube, std::vector<GLuint> &iboList, std::vector<GLuint> &vaoList, std::vector<GLuint> &vboList, GLuint VERTEX_ATTR_POSITION, GLuint VERTEX_ATTR_NORMAL, GLuint VERTEX_ATTR_TEXTURE){
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
    void CubeList::deleteCube(int index, std::vector<GLuint> &iboList, std::vector<GLuint> &vaoList, std::vector<GLuint> &vboList){
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

    // Translate
    void CubeList::translateCube(int index, GLfloat tx, GLfloat ty, GLfloat tz){
        m_cubeList[index].translateVertices(tx, ty, tz);
    };

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
    Eigen::VectorXd CubeList::RBF(Eigen::MatrixXd points){
        std::cout << "Trying hard to use radial basis function." << std::endl;
        // Build distances matrix
        /*Eigen::MatrixXd distances(points.rows(), points.rows());
        for(int xi=0; xi<points.rows(); xi++){
            std::cout << "x: " << points(xi, 0) << " y: " << points(xi, 1) << " z: " << points(xi, 2) << std::endl;
            for(int xj=0; xj<points.rows(); xj++){
                distances(xi,xj) = sqrt(pow(points(xj,0) - points(xi, 0), 2) +  
                pow(points(xj,1) - points(xi, 1), 2) +  
                pow(points(xj,2) - points(xi, 2), 2) * 1.0);
                std::cout << "Distance entre : " << xi << " et " << xj << " = " << distances(xi,xj) << std::endl;
            }
        }/*
        // Build weight vector (k unknown weights)
        Eigen::VectorXd w(points.rows());
        // Build z vector (size = points count)
        Eigen::VectorXd z(points.rows());
        for(int i=0; i<points.rows(); i++){
            z(i) = points(i, 2);
        }

        // Decompose distances matrix with LU
        /*std::cout << "Here is the distances matrix :" << std::endl << distances << std::endl;
        Eigen::FullPivLU<Eigen::MatrixXd> lu(distances);
        std::cout << "Here is, up to permutations, its LU decomposition matrix:"
            << std::endl << lu.matrixLU() << std::endl;
        std::cout << "Here is the L part:" << std::endl;
        int rows = points.rows();
        int cols = points.cols();
        Eigen::MatrixXd l = Eigen::MatrixXd::Identity(rows, rows);
        l.block(0,0, rows, cols).triangularView<Eigen::StrictlyLower>() = lu.matrixLU();
        std::cout << l << std::endl;
        std::cout << "Here is the U part:" << std::endl;
        Eigen::MatrixXd u = lu.matrixLU().triangularView<Eigen::Upper>();
        std::cout << u << std::endl;
        std::cout << "Let us now reconstruct the original matrix distances:" << std::endl;
        std::cout << lu.permutationP().inverse() * l * u * lu.permutationQ().inverse() << std::endl;
        // Find y = z*u
        //Eigen::MatrixXd y = z*u;
        std::cout << "Here is y :" << std::endl;
        Eigen::VectorXd y(u.rows());
        for(int i=u.rows(); i>0; i--){
            double sum = 0;
            if(i<u.rows()){
                for(int j=u.rows(); j>i; j--){
                    sum += y(j);
                }
            }
            y(i) = (z(i) - sum)/
        }
        std::cout << z/u << std::endl;*/

        // Solve distances*w = z
        int rows = points.rows();
        int cols = points.cols();

        Eigen::MatrixXd A(rows, rows);
        Eigen::VectorXd x(points.rows()), b(points.rows());
        //fill A
        for(int xi=0; xi<points.rows(); xi++){
            for(int xj=0; xj<points.rows(); xj++){
                float distance = sqrt(pow(points(xj,0) - points(xi, 0), 2) +  
                pow(points(xj,1) - points(xi, 1), 2) +  
                pow(points(xj,2) - points(xi, 2), 2));
                //A.insert(xi,xj) = exp( -distance);
                //A.insert(xi,xj) = 1/(1+sqrt(1+distance));
                A(xi,xj) = distance;
                //A(xi,xj) = -exp(-pow(-0.2*distance,2));
                //A(xi,xj) = pow((1+pow(0.2*distance, 2)), -1);
                std::cout << "Distance entre : " << xi << " et " << xj << " = " << A(xi,xj) << std::endl;
            }
        }
        std::cout << "Here is A:" << std::endl;
        std::cout << A << std::endl;
        //fill b
        for(int i=0; i<points.rows(); i++){
            b(i) = points(i, 2);
        }
        std::cout << "Here is b:" << std::endl;
        std::cout << b << std::endl;
        x = A.colPivHouseholderQr().solve(b);
        std::cout << "The solution is:\n" << x << std::endl;
        /*Eigen::VectorXd x(points.rows()), b(points.rows());
        Eigen::SparseMatrix<double> A(rows, rows);
        Eigen::SparseLU<Eigen::SparseMatrix<double>, Eigen::COLAMDOrdering<int> >   solver;
        // fill A and b;
        for(int xi=0; xi<points.rows(); xi++){
            for(int xj=0; xj<points.rows(); xj++){
                float distance = sqrt(pow(points(xj,0) - points(xi, 0), 2) +  
                pow(points(xj,1) - points(xi, 1), 2) +  
                pow(points(xj,2) - points(xi, 2), 2));
                //A.insert(xi,xj) = exp( -distance);
                //A.insert(xi,xj) = 1/(1+sqrt(1+distance));
                A.insert(xi,xj) = distance;
                std::cout << "Distance entre : " << xi << " et " << xj << " = " << A.coeff(xi,xj) << std::endl;
            }
        }
        std::cout << "Here is A:" << std::endl;
        std::cout << A << std::endl;
        for(int i=0; i<points.rows(); i++){
            b(i) = points(i, 2);
        }
        std::cout << "Here is b:" << std::endl;
        std::cout << b << std::endl;
        // Compute the ordering permutation vector from the structural pattern of A
        solver.analyzePattern(A); 
        // Compute the numerical factorization 
        solver.factorize(A); 
        //Use the factors to solve the linear system 
        x = solver.solve(b); 
        std::cout << "Here is w:" << std::endl;
        std::cout << x << std::endl;*/

        return x;
        
        //Test
        /*for(int i=1; i<points.rows(); i++){
            std::cout << "x: " << points(i, 0) << " y: " << points(i, 1) << " z: " << points(i, 2) << std::endl;
            GLfloat distance = sqrt(pow(points(i,0) - points(i-1, 0), 2) +  
                pow(points(i,1) - points(i-1, 1), 2) +  
                pow(points(i,2) - points(i-1, 2), 2) * 1.0);
            std::cout << "Distance entre : " << i << " et " << i-1 << " = " << distance << std::endl;
        }
        //pour chaque point consécutif jusqu'à la fin de la matrice points:
            //calculer la distance entre les deux points consécutifs
            //calculer la multiquadrique : sqrt(1+(epsilon*d)²)
            //ou alors pour les premiers test : function(d)=d
        /*GLfloat distance = sqrt(pow(points[1][0] - points[0][0], 2) +  
                pow(points[1][1] - points[0][1], 2) +  
                pow(points[1][2] - points[0][2], 2) * 1.0);*/
        //pour chaque points de controle
            //resoudre systeme (somme des distances de tous les pts consécutifs x/y)*poidsInconnu = z
            //Step 1 : create Mat(distances) // create w_i vector(k) // create z_i vector(k) (k=size=points.size())
            //Step 2 : decompose A lu_decomp Eigen
                /*
                Matrix5x3 m = Matrix5x3::Random();
                cout << "Here is the matrix m:" << endl << m << endl;
                Eigen::FullPivLU<Matrix5x3> lu(m);
                cout << "Here is, up to permutations, its LU decomposition matrix:"
                    << endl << lu.matrixLU() << endl;
                cout << "Here is the L part:" << endl;
                Matrix5x5 l = Matrix5x5::Identity();
                l.block<5,3>(0,0).triangularView<StrictlyLower>() = lu.matrixLU();
                cout << l << endl;
                cout << "Here is the U part:" << endl;
                Matrix5x3 u = lu.matrixLU().triangularView<Upper>();
                cout << u << endl;
                cout << "Let us now reconstruct the original matrix m:" << endl;
                cout << lu.permutationP().inverse() * l * u * lu.permutationQ().inverse() << endl;
                */
            //Step 3 : b / A_lu.upper = y(à trouver)
            //Step 4 : y / A_lu.lower = x(à trouver) 

        // return matrice(vecteur?) de poids == x
    }
    //Entrée: x et y random dans l'enceinte de la grille -- Sortie : z calculé grâce aux poids trouvés au-dessus
    double CubeList::interpolatePoints(double x, double y, Eigen::MatrixXd points){
        //g(x,y) = sum(w_i*rbf(|(x,y)-(xi, yi)))
        double z=0;
        Eigen::VectorXd w = this->RBF(points);
        for(int i=0; i<points.rows(); i++){
            double distance = sqrt(pow(points(i,0) - x, 2) +  
                pow(points(i,1) - y, 2) +  
                pow(points(i,2) - 0, 2) * 1.0);
            z += w(i)*distance;
        }
        std::cout << "ZZZ:" << z << std::endl;
        return (int)z;
    }

    void CubeList::save(std::string filepath, int item_LightD, std::vector<int> positionLightD, int item_LightP, std::vector<int> positionLightP){
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
        +std::to_string(positionLightD[2])+"\n";

        file << std::to_string(item_LightP)+" "
        +std::to_string(positionLightP[0])+" "
        +std::to_string(positionLightP[1])+" "
        +std::to_string(positionLightP[2])+"\n";
        
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

    void CubeList::load(std::vector<int> file, std::vector<GLuint> &iboList, std::vector<GLuint> &vaoList, std::vector<GLuint> &vboList, GLuint VERTEX_ATTR_POSITION, GLuint VERTEX_ATTR_NORMAL, GLuint VERTEX_ATTR_TEXTURE, std::vector<int> &cursorPosition, int &currentActive, int &item_LightD, std::vector<int> &positionLightD, int &item_LightP, std::vector<int> &positionLightP){
        std::cout << "Loading... " << (file.size()-2)/5 << "...cubes" << std::endl; 
        for(int i=0; i<file.size()-8; i+=5){
            this->addCube(Cube(), iboList, vaoList, vboList, VERTEX_ATTR_POSITION, VERTEX_ATTR_NORMAL, VERTEX_ATTR_TEXTURE);
            this->setTrans(file[i], file[i+1],file[i+2],file[i+3]);
            this->setTextureIndex(file[i], file[i+4]);
            if(this->getTrans(i).x==cursorPosition[0] && this->getTrans(i).y==cursorPosition[1] && this->getTrans(i).z==cursorPosition[2]){
                currentActive = this->getSize()-1;
            }
        }
        item_LightD = file[file.size()-8];
        positionLightD = {file[file.size()-7], file[file.size()-6],file[file.size()-5]};
        item_LightP = file[file.size()-4];
        positionLightP = {file[file.size()-3], file[file.size()-2],file[file.size()-1]};
    }

}

