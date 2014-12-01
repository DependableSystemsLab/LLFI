// $ANTLR 2.7.7 (20060906): "DOTRecord.g" -> "DOTRecordWalker.java"$

package net.claribole.zgrviewer.dot;

import antlr.TreeParser;
import antlr.Token;
import antlr.collections.AST;
import antlr.RecognitionException;
import antlr.ANTLRException;
import antlr.NoViableAltException;
import antlr.MismatchedTokenException;
import antlr.SemanticException;
import antlr.collections.impl.BitSet;
import antlr.ASTPair;
import antlr.collections.impl.ASTArray;


public class DOTRecordWalker extends antlr.TreeParser       implements DOTRecordTokenTypes
 {
public DOTRecordWalker() {
	tokenNames = _tokenNames;
}

	public final void record(AST _t,
		Object root, Record r
	) throws RecognitionException, Exception {
		
		AST record_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
		try {      // for error handling
			AST __t29 = _t;
			AST tmp11_AST_in = (AST)_t;
			match(_t,APOS);
			_t = _t.getFirstChild();
			record_label(_t,root, r);
			_t = _retTree;
			_t = __t29;
			_t = _t.getNextSibling();
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
	}
	
	public final void record_label(AST _t,
		Object g, Record r
	) throws RecognitionException, Exception {
		
		AST record_label_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		
		try {      // for error handling
			{
			_loop34:
			do {
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case PIPE:
				{
					AST __t32 = _t;
					AST tmp12_AST_in = (AST)_t;
					match(_t,PIPE);
					_t = _t.getFirstChild();
					{
					if (_t==null) _t=ASTNULL;
					switch ( _t.getType()) {
					case LT:
					case STR:
					case LCUR:
					{
						sibling_field(_t,g, r);
						_t = _retTree;
						break;
					}
					case 3:
					{
						break;
					}
					default:
					{
						throw new NoViableAltException(_t);
					}
					}
					}
					_t = __t32;
					_t = _t.getNextSibling();
					break;
				}
				case LT:
				case STR:
				case LCUR:
				{
					sibling_field(_t,g, r);
					_t = _retTree;
					break;
				}
				default:
				{
					break _loop34;
				}
				}
			} while (true);
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
	}
	
	public final void sibling_field(AST _t,
		Object g, Record r
	) throws RecognitionException, Exception {
		
		AST sibling_field_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		SubRecord sub = new SubRecord(g, "", r); String s="";
		
		try {      // for error handling
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case LT:
			case STR:
			{
				fieldID(_t,sub);
				_t = _retTree;
				break;
			}
			case LCUR:
			{
				AST __t37 = _t;
				AST tmp13_AST_in = (AST)_t;
				match(_t,LCUR);
				_t = _t.getFirstChild();
				record_label(_t,g, sub);
				_t = _retTree;
				_t = __t37;
				_t = _t.getNextSibling();
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
	}
	
	public final void fieldID(AST _t,
		Record r
	) throws RecognitionException {
		
		AST fieldID_AST_in = (_t == ASTNULL) ? null : (AST)_t;
		AST i = null;
		AST s = null;
		AST l = null;
		
		try {      // for error handling
			{
			if (_t==null) _t=ASTNULL;
			switch ( _t.getType()) {
			case LT:
			{
				AST __t40 = _t;
				AST tmp14_AST_in = (AST)_t;
				match(_t,LT);
				_t = _t.getFirstChild();
				i = (AST)_t;
				match(_t,STR);
				_t = _t.getNextSibling();
				{
				if (_t==null) _t=ASTNULL;
				switch ( _t.getType()) {
				case STR:
				{
					s = (AST)_t;
					match(_t,STR);
					_t = _t.getNextSibling();
					r.label = s.getText();
					break;
				}
				case 3:
				{
					break;
				}
				default:
				{
					throw new NoViableAltException(_t);
				}
				}
				}
				_t = __t40;
				_t = _t.getNextSibling();
				r.id = i.getText();
				break;
			}
			case STR:
			{
				l = (AST)_t;
				match(_t,STR);
				_t = _t.getNextSibling();
				r.label = l.getText();
				break;
			}
			default:
			{
				throw new NoViableAltException(_t);
			}
			}
			}
		}
		catch (RecognitionException ex) {
			reportError(ex);
			if (_t!=null) {_t = _t.getNextSibling();}
		}
		_retTree = _t;
	}
	
	
	public static final String[] _tokenNames = {
		"<0>",
		"EOF",
		"<2>",
		"NULL_TREE_LOOKAHEAD",
		"APOS",
		"LT",
		"STR",
		"GT",
		"LCUR",
		"RCUR",
		"PIPE",
		"WS",
		"ESC"
	};
	
	}
	
