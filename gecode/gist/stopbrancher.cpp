/* -*- mode: C++; c-basic-offset: 2; indent-tabs-mode: nil -*- */
/*
 *  Main authors:
 *     Guido Tack <tack@gecode.org>
 *
 *  Copyright:
 *     Guido Tack, 2006
 *
 *  Last modified:
 *     $Date: 2009-05-09 09:09:53 +0200 (Sat, 09 May 2009) $ by $Author: tack $
 *     $Revision: 9052 $
 *
 *  This file is part of Gecode, the generic constraint
 *  development environment:
 *     http://www.gecode.org
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <gecode/gist/stopbrancher.hh>

namespace Gecode { namespace Gist {

  StopChoice::StopChoice(const Brancher& b) : Choice(b,1) {}
  size_t
  StopChoice::size(void) const {
    return sizeof(StopChoice);
  }

  StopBrancher::StopBrancher(Home home) : Brancher(home), done(false) {}

  StopBrancher::StopBrancher(Space& home, bool share, StopBrancher& b)
    : Brancher(home, share, b), done(b.done) {}

  bool
  StopBrancher::status(const Space&) const {
    return !done;
  }

  Choice*
  StopBrancher::choice(Space&) {
    return new StopChoice(*this);
  }
  ExecStatus
  StopBrancher::commit(Space&, const Choice&, unsigned int) {
    done = true;
    return ES_OK;
  }
  Actor*
  StopBrancher::copy(Space& home, bool share) {
    return new (home) StopBrancher(home, share, *this);
  }
  void
  StopBrancher::post(Home home) {
    (void) new (home) StopBrancher(home);
  }
  size_t
  StopBrancher::dispose(Space&) {
    return sizeof(*this);
  }
  
}}

// STATISTICS: gist-any