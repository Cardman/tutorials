using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HelloWorld
{
    class Score
    {
        private int scoreLocal;

        private int scoreVisiteur;

        private String commentaire;

        private static int _nbInstances_ = 0;

        public Score() {
            _nbInstances_ ++;
        }

        public Score(int _scoreLocal, int _scoreVisiteur) {
            setScoreLocal(_scoreLocal);
            setScoreVisiteur(_scoreVisiteur);
            resume();
            _nbInstances_++;
        }

        public static int getNbInstances() {
            return _nbInstances_;
        }

        public void resume() {
            String commentaire_;
            if (scoreLocal < scoreVisiteur) {
                commentaire_ = "Nul ne doit etre sur de gagner";
                commentaire_ += " a domicile car il y a ";
                commentaire_ += scoreLocal;
                commentaire_ += " - ";
                commentaire_ += scoreVisiteur;
                commentaire_ += ", les visiteurs ont gagne.";
                commentaire = commentaire_;
                return;
            }
            if (scoreLocal == scoreVisiteur)
            {
                commentaire_ = "Accrochage";
                commentaire_ += " a domicile car il y a ";
                commentaire_ += scoreLocal;
                commentaire_ += " - ";
                commentaire_ += scoreVisiteur;
                commentaire_ += ", match nul.";
                commentaire = commentaire_;
                return;
            }
            commentaire_ = "Les locaux ont gere";
            commentaire_ += " leur maison car il y a ";
            commentaire_ += scoreLocal;
            commentaire_ += " - ";
            commentaire_ += scoreVisiteur;
            commentaire_ += ", les locaux ont gagne.";
            commentaire = commentaire_;
        }
        public void setScoreLocal(int _scoreLocal) {
            scoreLocal = _scoreLocal;
        }
        public void setScoreVisiteur(int _scoreVisiteur) {
            scoreVisiteur = _scoreVisiteur;
        }
        public String getCommentaire() {
            return commentaire;
        }
    }
}
