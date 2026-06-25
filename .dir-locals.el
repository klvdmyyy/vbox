;;; Directory Local Variables            -*- no-byte-compile: t -*-
;;; For more information see (info "(emacs) Directory Variables")

((nil . ((eval . (setq-local tags-file-name (if (project-current) (expand-file-name "TAGS" (project-root (project-current))) nil)))
	 )))